using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CRC
{
    public class CRCAlg
    {
        private BitArray polynom;

        public void SetPolynom(BitArray p)
        {
            // firs bit on start
            int i = p.Length - 1;
            while (i >= 0 && !p.Get(i))
            {
                i--;
            }

            if (i < 0)
            {
                polynom = new BitArray(1, false);
                return;
            }

            polynom = new BitArray(i + 1, false);
            polynom = new BitArray(p.Length);
            polynom.Or(p);
        }

        public void HashFile(string filename, string hashFilename)
        {
            // block size is one byte
            FileInfo fileInfo = new FileInfo(filename);
            BitArray result = new BitArray(polynom.Length - 1);

            using (var read = new BinaryReader(File.Open(filename, FileMode.Open)))
            {
                BitArray block = new BitArray(8 + polynom.Length - 1), info = new BitArray(8);
                for (int i = 0; i < fileInfo.Length; i++)
                {
                    BitArray pom = new BitArray(new byte[] { read.ReadByte() });
                    pom.Length = info.Length;
                    info.Or(pom);
                    for (int k = 0; k < 8; k++)
                    {
                        block[polynom.Length - 1 + k] = info[k];
                    }

                    result.Xor(HashBlock(block));
                }
                
            }
            using (var write = new BinaryWriter(File.Open(hashFilename, FileMode.Create)))
            {
                byte[] hash = new byte[((result.Length - 1) >> 3) + 1];
                result.CopyTo(hash, 0);
                foreach(var a in hash)
                {
                    write.Write(a);
                }
            }
        }

        public BitArray HashBlock(BitArray block)
        {
            BitArray result = new BitArray(block);
            // block is shifted by polynom degree

            // divide:
            for (int i = polynom.Length; i >= this.polynom.Length; i--)
            {
                if (result.Get(i - 1))
                {
                    // subtract:
                    for (int k = polynom.Length; k > 0; k--)
                    {
                        result[i - k] = polynom[k - 1] != result[i - k] ? true : false; // XOR
                    }
                }
            }
            result.Length = polynom.Length - 1;
            return result;
        }
    }
}
