// Unit test for InDevFeeWindow() -- the time-based dev-fee gate (clean-stack/miner/devfee_window.h).
// A bug here changes the actual fee rate every miner pays. Standalone: no btx, no core, no sockets.
//   cmake --build <build> --target devfee_window_test && ./<build>/devfee_window_test   (exit 0 = pass)
//
// btxluxminer fork: the mandatory fee is 2.5% (kDevFeeMinPct), i.e. 90s of every 3600.
// These tests anchor on that value so a regression in the fork's fee is caught here.
#include "../miner/devfee_window.h"

#include <cmath>
#include <cstdio>
#include <initializer_list>
#include <string>

static int g_fail = 0;
static void check(bool cond, const char* expr)
{
    std::printf(cond ? "  ok   %s\n" : "  FAIL %s\n", expr);
    if (!cond) ++g_fail;
}
#define CHECK(x) check((x), #x)

int main()
{
    std::printf("[devfee_window_test]\n");
    const double P = 3600.0;   // kPoolDevPeriodSec (1 hour); devfee=2.5 -> 90s window

    // --- The fork's actual fee: 2.5% == first 90s of each period ---
    CHECK(InDevFeeWindow(0.0,    P, 2.5));    // pos=0    < 90
    CHECK(InDevFeeWindow(89.9,   P, 2.5));    // pos=89.9 < 90
    CHECK(!InDevFeeWindow(90.0,  P, 2.5));    // pos=90   NOT < 90
    CHECK(!InDevFeeWindow(100.0, P, 2.5));    // pos=100  outside

    // The window repeats every period (mod), not just the first hour.
    CHECK(InDevFeeWindow(P + 0.0,    P, 2.5));    // pos=0 next period
    CHECK(InDevFeeWindow(P + 89.9,   P, 2.5));
    CHECK(!InDevFeeWindow(P + 90.0,  P, 2.5));
    CHECK(InDevFeeWindow(100 * P + 10.0, P, 2.5));   // still works far out

    // devfee off -> never in window (no fee charged).
    CHECK(!InDevFeeWindow(0.0,  P, 0.0));
    CHECK(!InDevFeeWindow(10.0, P, 0.0));

    // Bigger fee widens the window proportionally (5% -> 180s).
    CHECK(InDevFeeWindow(179.0,  P, 5.0));
    CHECK(!InDevFeeWindow(181.0, P, 5.0));

    // Fractional percents must work (this is why the gate takes a double).
    CHECK(InDevFeeWindow(89.0,  P, 2.5));    // inside the 2.5% window
    CHECK(!InDevFeeWindow(91.0, P, 2.5));    // just outside it

    // Fee-RATE property: fraction of wall-clock in the window == devfee% (the whole point).
    // Integer percents: window = 36*pct is an exact number of 1s samples.
    for (int pct : {1, 5, 10}) {
        int in = 0;
        for (int s = 0; s < 3600; ++s) if (InDevFeeWindow(static_cast<double>(s), P, pct)) ++in;
        const int expect = 36 * pct;
        check(in == expect, (std::string("fee-rate ") + std::to_string(pct) + "% == "
                             + std::to_string(in) + "/3600").c_str());
    }

    // Fee-RATE for the fork's 2.5%: window is 90s, so a 1s sweep counts exactly 90.
    {
        int in = 0;
        for (int s = 0; s < 3600; ++s) if (InDevFeeWindow(static_cast<double>(s), P, 2.5)) ++in;
        check(in == 90, (std::string("fee-rate 2.5% == ") + std::to_string(in) + "/3600 (want 90)").c_str());
    }

    if (g_fail == 0) std::printf("ALL PASS\n");
    else             std::printf("%d FAILED\n", g_fail);
    return g_fail == 0 ? 0 : 1;
}
