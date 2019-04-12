#include <iostream>
#include <vector>

#include "readxml.h"
#include "interval.hpp"
#include "intervalsoutput.h"
#include "findprimes.h"
#include "primesconsoleoutput.h"
#include "primesfileoutput.h"

int main()
{
    const char *pFileName1 = "C:/Users/Workstation/Documents/CPP/PrimesProject 2/test.xml";
    const char *pFileName2 = "C:/Users/Workstation/Documents/CPP/PrimesProject 2/primes.xml";
    std::vector <Interval> IntVc;

    ReadXml xml1(pFileName1, { "root" });
    xml1.setOutput(new IntervalsOutput(&IntVc));
    xml1.output();

    for(uint32_t i = 0, p = IntVc.size(); i < p; ++i)
        std::cout << "Low: " << IntVc[i].m_nLowIntervalSide << ", High: " << IntVc[i].m_nHighIntervalSide << '\n';
    std::cout << '\n';

    FindPrimes PrimeNumbers(&IntVc);

    PrimeNumbers.setOutput(new PrimesConsoleOutput());
    PrimeNumbers.output();

    PrimeNumbers.setOutput(new PrimesFileOutput(pFileName2));
    PrimeNumbers.output();

    return 0;
}
