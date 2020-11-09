using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static FileFunctions.FileFunctions;

namespace RC4
{
    public class RC4Alg
    {
        // A1:
        public void Crypt(String filename, String resultFile, byte[] key)
        {
            byte[] K = new byte[256], S = new byte[256];

            byte br = 0;
            for (int i = 0; i < 256; i++)
            {
                S[i] = br++;
                K[i] = key[i % key.Length];
            }
            int k = 0;
            for (int i = 0; i < 256; i++)
            {
                k = (k + S[i] + K[i]) % 256;

                byte pom = S[i];
                S[i] = S[k];
                S[k] = pom;
            }

            int g = 0, t;
            k = 0;

            byte[] info = ReadBytes(filename);
            byte[] result = new byte[info.Length];

            for (int i = 0; i < info.Length; i++)
            {
                g = (g + 1) % 256;
                k = (k + S[g]) % 256;

                byte pom = S[g];
                S[g] = S[k];
                S[k] = pom;

                t = S[(S[g] + S[k]) % 256];

                result[i] = BitConverter.GetBytes(t ^ info[i])[0] ;
            }

            WriteBytes(resultFile, result);
        }

        public void Decrypt(String filename, String resultFile, byte[] key)
        {
            Crypt(filename, resultFile, key);
        }
    }
}
