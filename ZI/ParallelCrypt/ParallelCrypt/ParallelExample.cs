/*
 * Refferences:
 * https://dejanstojanovic.net/aspnet/2018/march/download-file-in-chunks-in-parallel-in-c/
 */

using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using ARC4;

namespace ParallelCrypt
{
    public class ParallelExample
    {
        //public void ParallelBifidCrypt(String filename, String resultFile, byte[] key) // key length 26 (key[0] - period; key[1-25] matrix)
        //{
        //    byte period = key[0], firstChar = Convert.ToByte('a'), jValue = Convert.ToByte('j');
        //    byte[] keyRow = new byte[25], keyColumn = new byte[25], textRow = new byte[period], textColumn = new byte[period];

        //    int index = 1;
        //    for (byte i = 0; i < 5; i++)
        //    {
        //        for (byte k = 0; k < 5; k++)
        //        {
        //            //index = i * 5 + k + 1;
        //            int keyValue = key[index++];
        //            if (jValue < keyValue)
        //            {
        //                keyValue--;
        //            }

        //            keyRow[keyValue - firstChar] = i;
        //            keyColumn[keyValue - firstChar] = k;
        //        }
        //    }

        //    // parallelized:

        //    FileInfo fileInfo = new FileInfo(filename);
        //    long fileLength = fileInfo.Length;
        //    long loopNumber = (fileLength / blockSize) + (fileLength % blockSize == 0 ? 0 : 1);

        //    ConcurrentDictionary<int, String> tempFilesDictionary = new ConcurrentDictionary<int, String>();
        //    //int index = 0;

        //    Parallel.For(0, loopNumber, new ParallelOptions() { MaxDegreeOfParallelism = threadNumber }, (index) =>
        //    {

        //        using (BinaryReader reader = new BinaryReader(File.OpenRead(cipherFile)))
        //        {
        //            byte[] cipher = new byte[blockSize];
        //            reader.BaseStream.Seek(blockSize * index, SeekOrigin.Begin);
        //            reader.Read(cipher, 0, blockSize);

        //            // crypt:

        //            byte[] result = alg.CryptBlock(cipher);

        //            // store cipher in temp file:
        //            String tempFilePath = Path.GetTempFileName();
        //            using (BinaryWriter writer = new BinaryWriter(File.Open(tempFilePath, FileMode.Create)))
        //            {
        //                writer.Write(result);

        //                // remember filename:
        //                tempFilesDictionary.TryAdd((int)index, tempFilePath);
        //            }
        //        }
        //    });

        //    // merge temp files:
        //    using (BinaryWriter finalWriter = new BinaryWriter(File.Open(resultFile, FileMode.Create)))
        //    {
        //        foreach (var tempFile in tempFilesDictionary.OrderBy(b => b.Key))
        //        {
        //            byte[] tempFileBytes = File.ReadAllBytes(tempFile.Value);
        //            finalWriter.Write(tempFileBytes);
        //            File.Delete(tempFile.Value);
        //        }
        //    }

        //    int count = 0;
        //    index = 0;
        //    List<char> letters = ReadAllLettersBifid(filename);
        //    byte[] cipher = new byte[letters.Count];
        //    foreach (var l in letters)
        //    {
        //        byte value = Convert.ToByte(l);
        //        if (jValue < value)
        //        {
        //            value--;
        //        }
        //        textRow[index] = keyRow[value - firstChar];
        //        textColumn[index++] = keyColumn[value - firstChar];

        //        // crypt period:
        //        if (index == period || count == letters.Count - 1)
        //        {
        //            byte[] p = new byte[index * 2];
        //            for (int i = 0; i < index; i++)
        //            {
        //                p[i] = textRow[i];
        //            }
        //            for (int i = 0; i < index; i++)
        //            {
        //                p[i + index] = textColumn[i];
        //            }

        //            int pomInd = count - index + 1;
        //            for (int i = 0; i < index * 2; i += 2)
        //            {
        //                cipher[pomInd++] = key[(p[i]) * 5 + p[i + 1] + 1];
        //            }

        //            index = 0;
        //        }

        //        count++;
        //    }

        //    WriteAllLettersBifid(resultFile, cipher);
        //}

        //public void ParallelBifidDecrypt(String filename, String resultFile, byte[] key)
        //{
        //    byte period = key[0], firstChar = Convert.ToByte('a'), jValue = Convert.ToByte('j');
        //    byte[] keyRow = new byte[25], keyColumn = new byte[25], cipherRow = new byte[period], cipherColumn = new byte[period];

        //    int index = 1;
        //    for (byte i = 0; i < 5; i++)
        //    {
        //        for (byte k = 0; k < 5; k++)
        //        {
        //            //index = i * 5 + k + 1;
        //            int keyValue = key[index++];
        //            if (jValue < keyValue)
        //            {
        //                keyValue--;
        //            }

        //            keyRow[keyValue - firstChar] = i;
        //            keyColumn[keyValue - firstChar] = k;
        //        }
        //    }

        //    // parallelized:

        //    int count = 0;
        //    index = 0;
        //    List<char> letters = ReadAllLettersBifid(filename);
        //    byte[] text = new byte[letters.Count];
        //    foreach (var l in letters)
        //    {
        //        byte value = Convert.ToByte(l);
        //        if (jValue < value)
        //        {
        //            value--;
        //        }
        //        cipherRow[index] = keyRow[value - firstChar];
        //        cipherColumn[index++] = keyColumn[value - firstChar];

        //        // decrypt period:
        //        if (index == period || count == letters.Count - 1)
        //        {
        //            byte[] p = new byte[index * 2];
        //            int k = 0;
        //            for (int i = 0; i < index * 2; i += 2)
        //            {
        //                p[i] = cipherRow[k];
        //                p[i + 1] = cipherColumn[k++];
        //            }

        //            int pomInd = count - index + 1;
        //            for (int i = 0; i < index; i++)
        //            {
        //                text[pomInd++] = key[(p[i]) * 5 + p[i + index] + 1];
        //            }

        //            index = 0;
        //        }

        //        count++;
        //    }

        //    WriteAllLettersBifid(resultFile, text);

        //}


        public static void ParallelizeARC4AlgCrypt(string plainFile, string resultFile, byte[] key, int threadNumber, int blockSize)
        {
            ARC4Alg alg = new ARC4Alg();
            FileInfo fileInfo = new FileInfo(plainFile);
            long fileLength = fileInfo.Length;
            long loopNumber = (fileLength / blockSize) + (fileLength % blockSize == 0 ? 0 : 1);

            ConcurrentDictionary<int, String> tempFilesDictionary = new ConcurrentDictionary<int, String>();
            //int index = 0;

            Parallel.For(0, loopNumber, new ParallelOptions() { MaxDegreeOfParallelism = threadNumber }, (index) =>
            {

                using (BinaryReader reader = new BinaryReader(File.OpenRead(plainFile)))
                {
                    byte[] plainText = new byte[blockSize];
                    reader.BaseStream.Seek(blockSize * index, SeekOrigin.Begin);
                    int length = reader.Read(plainText, 0, blockSize);

                    if (length > 0)
                    {
                        // crypt:
                        byte[] shortPlain = new byte[length];
                        if (length < blockSize)
                        {
                            for (int i = 0; i < length; i++)
                            {
                                shortPlain[i] = plainText[i];
                            }
                        }

                        byte[] cipher = alg.CryptBlock(shortPlain, key);

                        // store cipher in temp file:
                        String tempFilePath = Path.GetTempFileName();
                        using (BinaryWriter writer = new BinaryWriter(File.Open(tempFilePath, FileMode.Create)))
                        {
                            writer.Write(cipher);

                            // remember filename:
                            tempFilesDictionary.TryAdd((int)index, tempFilePath);
                        }
                    }
                }
            });

            // merge temp files:
            using (BinaryWriter finalWriter = new BinaryWriter(File.Open(resultFile, FileMode.Create)))
            {
                foreach (var tempFile in tempFilesDictionary.OrderBy(b => b.Key))
                {
                    byte[] tempFileBytes = File.ReadAllBytes(tempFile.Value);
                    finalWriter.Write(tempFileBytes);
                    File.Delete(tempFile.Value);
                }
            }
        }

        public static void ParallelizeARC4AlgDecrypt(string cipherFile, string resultFile, byte[] key, int threadNumber, int blockSize)
        {
            ARC4Alg alg = new ARC4Alg();
            FileInfo fileInfo = new FileInfo(cipherFile);
            long fileLength = fileInfo.Length;
            long loopNumber = (fileLength / blockSize) + (fileLength % blockSize == 0 ? 0 : 1);

            ConcurrentDictionary<int, String> tempFilesDictionary = new ConcurrentDictionary<int, String>();
            //int index = 0;

            Parallel.For(0, loopNumber, new ParallelOptions() { MaxDegreeOfParallelism = threadNumber }, (index) =>
            {

                using (BinaryReader reader = new BinaryReader(File.OpenRead(cipherFile)))
                {
                    byte[] cipher = new byte[blockSize];
                    reader.BaseStream.Seek(blockSize * index, SeekOrigin.Begin);
                    int length = reader.Read(cipher, 0, blockSize);

                    if (length > 0)
                    {
                        // crypt:
                        byte[] shortCipher = new byte[length];
                        if (length < blockSize)
                        {
                            for (int i = 0; i < length; i++)
                            {
                                shortCipher[i] = cipher[i];
                            }
                        }
                        byte[] result = alg.DecryptBlock(shortCipher, key);

                        // store cipher in temp file:
                        String tempFilePath = Path.GetTempFileName();
                        using (BinaryWriter writer = new BinaryWriter(File.Open(tempFilePath, FileMode.Create)))
                        {
                            writer.Write(result);

                            // remember filename:
                            tempFilesDictionary.TryAdd((int)index, tempFilePath);
                        }
                    }
                }
            });

            // merge temp files:
            using (BinaryWriter finalWriter = new BinaryWriter(File.Open(resultFile, FileMode.Create)))
            {
                foreach (var tempFile in tempFilesDictionary.OrderBy(b => b.Key))
                {
                    byte[] tempFileBytes = File.ReadAllBytes(tempFile.Value);
                    finalWriter.Write(tempFileBytes);
                    File.Delete(tempFile.Value);
                }
            }
        }
    }
}
