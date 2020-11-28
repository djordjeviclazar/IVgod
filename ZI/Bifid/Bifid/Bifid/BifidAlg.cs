using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static FileFunctions.FileFunctions;

namespace Bifid
{
    class BifidAlg
    {
        public void Crypt(String filename, String resultFile, byte[] key) // key length 26 (key[0] - period; key[1-25] matrix)
        {
            byte period = key[0], firstChar = Convert.ToByte('a'), jValue = Convert.ToByte('j');
            byte[] keyRow = new byte[25], keyColumn = new byte[25], textRow = new byte[period], textColumn = new byte[period];

            int index = 1;
            for (byte i = 0; i < 5; i++)
            {
                for (byte k = 0; k < 5; k++)
                {
                    //index = i * 5 + k + 1;
                    int keyValue = key[index++];
                    if (jValue < keyValue)
                    {
                        keyValue--;
                    }

                    keyRow[keyValue - firstChar] = i;
                    keyColumn[keyValue - firstChar] = k;
                }
            }

            int count = 0;
            index = 0;
            List<char> letters = ReadAllLettersBifid(filename);
            byte[] cipher = new byte[letters.Count];
            foreach (var l in letters)
            {
                byte value = Convert.ToByte(l);
                if (jValue < value)
                {
                    value--;
                }
                textRow[index] = keyRow[value - firstChar];
                textColumn[index++] = keyColumn[value - firstChar];

                // crypt period:
                if (index == period || count == letters.Count - 1)
                {
                    byte[] p = new byte[index * 2];
                    for (int i = 0; i < index; i++)
                    {
                        p[i] = textRow[i];
                    }
                    for (int i = 0; i < index; i++)
                    {
                        p[i + index] = textColumn[i];
                    }

                    int pomInd = count - index + 1;
                    for (int i = 0; i < index * 2; i += 2)
                    {
                        cipher[pomInd++] = key[(p[i]) * 5 +  p[i + 1] + 1];
                    }

                    index = 0;
                }

                count++;
            }

            WriteAllLettersBifid(resultFile, cipher);
        }

        public void Decrypt(String filename, String resultFile, byte[] key)
        {
            byte period = key[0], firstChar = Convert.ToByte('a'), jValue = Convert.ToByte('j');
            byte[] keyRow = new byte[25], keyColumn = new byte[25], cipherRow = new byte[period], cipherColumn = new byte[period];

            int index = 1;
            for (byte i = 0; i < 5; i++)
            {
                for (byte k = 0; k < 5; k++)
                {
                    //index = i * 5 + k + 1;
                    int keyValue = key[index++];
                    if (jValue < keyValue)
                    {
                        keyValue--;
                    }

                    keyRow[keyValue - firstChar] = i;
                    keyColumn[keyValue - firstChar] = k;
                }
            }

            int count = 0;
            index = 0;
            List<char> letters = ReadAllLettersBifid(filename);
            byte[]  text= new byte[letters.Count];
            foreach (var l in letters)
            {
                byte value = Convert.ToByte(l);
                if (jValue < value)
                {
                    value--;
                }
                cipherRow[index] = keyRow[value - firstChar];
                cipherColumn[index++] = keyColumn[value - firstChar];

                // decrypt period:
                if (index == period || count == letters.Count - 1)
                {
                    byte[] p = new byte[index * 2];
                    int k = 0;
                    for (int i = 0; i < index * 2; i += 2)
                    {
                        p[i] = cipherRow[k];
                        p[i + 1] = cipherColumn[k++];
                    }

                    int pomInd = count - index + 1;
                    for (int i = 0; i < index; i++)
                    {
                        text[pomInd++] = key[(p[i]) * 5 + p[i + index] + 1];
                    }

                    index = 0;
                }

                count++;
            }

            WriteAllLettersBifid(resultFile, text);

        }
    }
}
