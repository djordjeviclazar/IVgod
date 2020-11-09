using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RC4
{
    class Program
    {
        static void Main(string[] args)
        {
            RC4Alg alg = new RC4Alg();
            

            byte[] key = Encoding.ASCII.GetBytes("Key");
            FileFunctions.FileFunctions.WriteBytes("e.txt", key);
            alg.Crypt("Testfiles/A1B1PlainText1.ppt", "Testfiles/A1B1PlainText1Crypted.bin", key);
            alg.Decrypt("Testfiles/A1B1PlainText1Crypted.bin", "Resultfiles/A1B1PlainText1Decrypted.ppt", key);
        }
    }
}
