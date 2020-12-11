using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RSA
{
    class Program
    {
        static void Main(string[] args)
        {
            RSAAlg alg = new RSAAlg();
            alg.GenerateSmallKey();
            alg.Crypt("Testfiles/B2A.bmp", "Testfiles/B2ACrypted.bmp");
            alg.Crypt("Testfiles/B2ACrypted.bmp", "Testfiles/B2ADecrypted.bmp");
        }
    }
}
