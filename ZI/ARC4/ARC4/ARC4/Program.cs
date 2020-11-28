using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ARC4
{
    class Program
    {
        static void Main(string[] args)
        {
            ARC4Alg alg = new ARC4Alg();
            

            byte[] key = Encoding.ASCII.GetBytes("ALSFslkfnslaf");
            FileFunctions.FileFunctions.WriteBytes("e.txt", key);
            /*alg.Crypt("Testfiles/A1B1PlainText1.ppt", "Testfiles/A1B1PlainText1Crypted.bin", key);
            alg.Decrypt("Testfiles/A1B1PlainText1Crypted.bin", "Resultfiles/A1B1PlainText1Decrypted.ppt", key);
            alg.Crypt("Testfiles/A1B1PlainText2.docx", "Testfiles/A1B1PlainText2Crypted.bin", key);
            alg.Decrypt("Testfiles/A1B1PlainText2Crypted.bin", "Resultfiles/A1B1PlainText2Decrypted.docx", key);
            alg.Crypt("Testfiles/A1B1PlainText3.txt", "Testfiles/A1B1PlainText3Crypted.bin", key);
            alg.Decrypt("Testfiles/A1B1PlainText3Crypted.bin", "Resultfiles/A1B1PlainText3Decrypted.txt", key);*/
            alg.Crypt("Testfiles/B2A.bmp", "Testfiles/B2ACrypted.bmp", key);
            alg.Decrypt("Testfiles/B2ACrypted.bmp", "Resultfiles/B2ADecrypted.bmp", key);
            alg.Crypt("Testfiles/B2B.bmp", "Testfiles/B2BCrypted.bmp", key);
            alg.Decrypt("Testfiles/B2BCrypted.bmp", "Resultfiles/B2BDecrypted.bmp", key);
            alg.Crypt("Testfiles/B2C.bmp", "Testfiles/B2CCrypted.bmp", key);
            alg.Decrypt("Testfiles/B2CCrypted.bmp", "Resultfiles/B2CDecrypted.bmp", key);
            alg.Crypt("Testfiles/B2D.bmp", "Testfiles/B2DCrypted.bmp", key);
            alg.Decrypt("Testfiles/B2DCrypted.bmp", "Resultfiles/B2DDecrypted.bmp", key);
        }
    }
}
