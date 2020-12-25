using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ARC4;

namespace ParallelCrypt
{
    class Program
    {
        static void Main(string[] args)
        {
            ARC4Alg alg;


            byte[] key = Encoding.ASCII.GetBytes("ALSFslkfnslaf");
            //FileFunctions.FileFunctions.WriteBytes("e.txt", key);
            ParallelExample.ParallelizeARC4AlgCrypt("Testfiles/A1B1PlainText1.ppt", "Testfiles/A1B1PlainText1Crypted.bin", key, 2, 1024);
            ParallelExample.ParallelizeARC4AlgDecrypt("Testfiles/A1B1PlainText1Crypted.bin", "Resultfiles/A1B1PlainText1Decrypted.ppt", key, 2, 1024);
            ParallelExample.ParallelizeARC4AlgCrypt("Testfiles/A1B1PlainText2.docx", "Testfiles/A1B1PlainText2Crypted.bin", key, 2, 1024);
            ParallelExample.ParallelizeARC4AlgDecrypt("Testfiles/A1B1PlainText2Crypted.bin", "Resultfiles/A1B1PlainText2Decrypted.docx", key, 2, 1024);
            ParallelExample.ParallelizeARC4AlgCrypt("Testfiles/A1B1PlainText3.txt", "Testfiles/A1B1PlainText3Crypted.bin", key, 2, 1024);
            ParallelExample.ParallelizeARC4AlgDecrypt("Testfiles/A1B1PlainText3Crypted.bin", "Resultfiles/A1B1PlainText3Decrypted.txt", key, 2, 1024);
            /*
            alg = ParallelExample.ParallelizeARC4AlgCrypt("Testfiles/B2A.bmp", "Testfiles/B2ACrypted.bmp", key, 8, 1024);
            ParallelExample.ParallelizeARC4AlgDecrypt("Testfiles/B2ACrypted.bmp", "Resultfiles/B2ADecrypted.bmp", key, 8, 1024, alg);
            alg = ParallelExample.ParallelizeARC4AlgCrypt("Testfiles/B2B.bmp", "Testfiles/B2BCrypted.bmp", key, 8, 1024);
            ParallelExample.ParallelizeARC4AlgDecrypt("Testfiles/B2BCrypted.bmp", "Resultfiles/B2BDecrypted.bmp", key, 8, 1024, alg);
            alg = ParallelExample.ParallelizeARC4AlgCrypt("Testfiles/B2C.bmp", "Testfiles/B2CCrypted.bmp", key, 8, 1024);
            ParallelExample.ParallelizeARC4AlgDecrypt("Testfiles/B2CCrypted.bmp", "Resultfiles/B2CDecrypted.bmp", key, 8, 1024, alg);
            alg = ParallelExample.ParallelizeARC4AlgCrypt("Testfiles/B2D.bmp", "Testfiles/B2DCrypted.bmp", key, 8, 1024);
            ParallelExample.ParallelizeARC4AlgDecrypt("Testfiles/B2DCrypted.bmp", "Resultfiles/B2DDecrypted.bmp", key, 8, 1024, alg);*/
        }
    }
}
