using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ARC4;

namespace ParallelCrypt
{
    public class ParallelExample
    {
        static void ParallelizeARC4AlgCrypt(string plainFile, string resultFile, byte[] key, int threadNumber, int blockSize)
        {
            ARC4Alg alg = new ARC4Alg(key);
            FileInfo fileInfo = new FileInfo(plainFile);
            long fileLength = fileInfo.Length;
            long loopNumber = (fileLength / blockSize) + (fileLength % blockSize == 0 ? 0 : 1);

            ConcurrentDictionary<int, String> tempFilesDictionary = new ConcurrentDictionary<int, String>();
            int index = 0;

            Parallel.For(0, loopNumber, new ParallelOptions() { MaxDegreeOfParallelism = threadNumber }, readRange =>
            {
                
                using (BinaryReader reader =new BinaryReader(File.OpenRead(plainFile)))
                {
                    byte[] plainText = reader.ReadBytes(blockSize);

                    // crypt:

                    byte[] cipher = alg.CryptBlock(plainText);

                    // store cipher in temp file:
                    String tempFilePath = Path.GetTempFileName();
                    using (BinaryWriter writer = new BinaryWriter(File.Open(tempFilePath, FileMode.Create)))
                    {
                        writer.Write(cipher);

                        // remember filename:
                        tempFilesDictionary.TryAdd((int)index++, tempFilePath);
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

        static void ParallelizeARC4AlgDecrypt(string cipherFile, string resultFile, byte[] key, int threadNumber, int blockSize)
        {
            ARC4Alg alg = new ARC4Alg(key);
            FileInfo fileInfo = new FileInfo(cipherFile);
            long fileLength = fileInfo.Length;
            long loopNumber = (fileLength / blockSize) + (fileLength % blockSize == 0 ? 0 : 1);

            ConcurrentDictionary<int, String> tempFilesDictionary = new ConcurrentDictionary<int, String>();
            int index = 0;

            Parallel.For(0, loopNumber, new ParallelOptions() { MaxDegreeOfParallelism = threadNumber }, readRange =>
            {

                using (BinaryReader reader = new BinaryReader(File.OpenRead(cipherFile)))
                {
                    byte[] cipher = reader.ReadBytes(blockSize);

                    // crypt:

                    byte[] result = alg.CryptBlock(cipher);

                    // store cipher in temp file:
                    String tempFilePath = Path.GetTempFileName();
                    using (BinaryWriter writer = new BinaryWriter(File.Open(tempFilePath, FileMode.Create)))
                    {
                        writer.Write(result);

                        // remember filename:
                        tempFilesDictionary.TryAdd((int)index++, tempFilePath);
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
