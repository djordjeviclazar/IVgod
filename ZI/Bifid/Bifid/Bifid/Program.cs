using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bifid
{
    class Program
    {
        static void Main(string[] args)
        {
            byte period = 5;
            byte[] key = new byte[26], permutation = Encoding.ASCII.GetBytes("vfqmgxaylnohdkercpszwbuti");
            key[0] = period;
            for (int i = 0; i < 25; i++)
            {
                key[i + 1] = permutation[i];
            }

            BifidAlg alg = new BifidAlg();

            alg.Crypt("Testfiles/bible.txt", "Testfiles/bibleCrypted.txt", key);
            alg.Decrypt("Testfiles/bibleCrypted.txt", "Resultfiles/bibleDecrypted.txt", key);
            alg.Crypt("Testfiles/E.coli", "Testfiles/ECrypted.coli", key);
            alg.Decrypt("Testfiles/ECrypted.coli", "Resultfiles/EDecrypted.coli", key);
            alg.Crypt("Testfiles/world192.txt", "Testfiles/world192Crypted.txt", key);
            alg.Decrypt("Testfiles/world192Crypted.txt", "Resultfiles/world192Decrypted.txt", key);
        }
    }
}
