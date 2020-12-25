using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ARC4;

namespace CBC
{
    public class CBCMode
    {
        byte[] IV;

        public void Crypt(String filename, String resultFile, byte[] key, int blockSize)
        {
            // initialization vector:
            IV = new byte[blockSize];
            Random random = new Random();
            for (int i = 0; i < blockSize; i++)
            {
                random.NextBytes(IV);
            }

            //Crypt:
            ARC4Alg alg = new ARC4Alg(key);
            FileInfo fileInfo = new FileInfo(filename);
            long fileSize = fileInfo.Length;

            byte[] initVector = IV.ToArray();

            using (BinaryReader reader = new BinaryReader(File.OpenRead(filename)))
            {
                using(BinaryWriter writer = new BinaryWriter(File.Open(resultFile, FileMode.Create)))
                {
                    for (long i = 0; i < fileSize; i += blockSize)
                    {
                        byte[] plainText = reader.ReadBytes(blockSize);
                        if (plainText.Length == 0)
                        {
                            break;
                        }
                        byte[] modifiedText = new byte[plainText.Length];

                        for (int k = 0; k < plainText.Length; k++)
                        {
                            modifiedText[k] = BitConverter.GetBytes(initVector[k] ^ plainText[k])[0];
                        }

                        byte[] cipher = alg.CryptBlock(modifiedText);
                        writer.Write(cipher);

                        // prepare IV:
                        initVector = cipher; // if length of cipher is less i > fileLength
                    }
                }
            }

        }

        public void Decrypt(String filename, String resultFile, byte[] key, int blockSize)
        {
            ARC4Alg alg = new ARC4Alg(key);
            FileInfo fileInfo = new FileInfo(filename);
            long fileSize = fileInfo.Length;

            byte[] initVector = IV.ToArray();

            using (BinaryReader reader = new BinaryReader(File.OpenRead(filename)))
            {
                using (BinaryWriter writer = new BinaryWriter(File.Open(resultFile, FileMode.Create)))
                {
                    for (long i = 0; i < fileSize; i += blockSize)
                    {
                        byte[] cipher = reader.ReadBytes(blockSize);
                        if (cipher.Length == 0)
                        {
                            break;
                        }
                        

                        byte[] modifiedText = alg.DecryptBlock(cipher);

                        byte[] decoded = new byte[cipher.Length];

                        for (int k = 0; k < cipher.Length; k++)
                        {
                            decoded[k] = BitConverter.GetBytes(initVector[k] ^ cipher[k])[0];
                        }

                        writer.Write(decoded);

                        // prepare IV:
                        initVector = cipher; // if length of cipher is less i > fileLength
                    }
                }
            }
        }
    }
}
