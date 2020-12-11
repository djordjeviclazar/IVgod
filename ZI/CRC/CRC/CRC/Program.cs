using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CRC
{
    class Program
    {
        static void Main(string[] args)
        {
            CRCAlg alg = new CRCAlg();

            alg.SetPolynom(new BitArray(new bool[] { true, true, true, false, false, false, false, false, true })); // CRC-8, 0xD5
            alg.HashFile("Testfiles/0-9.txt", "Testfiles/0-9Hash.txt");
        }
    }
}
