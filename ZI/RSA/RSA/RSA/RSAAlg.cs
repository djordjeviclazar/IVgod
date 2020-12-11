using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace RSA
{
    public class RSAAlg
    {
        private BigInteger publicKey; // e
        private BigInteger privateKey; // d
        private int elementBytes; // number of bytes for element in crypted file
        private BigInteger n; // p * q

        public void GenerateSmallKey()
        {
            Random random = new Random();
            // generate p:
            BigInteger p = findGreaterPrime(Convert.ToInt32(random.NextDouble() * 1_000_000) );
            // generate q:
            BigInteger q = findGreaterPrime(Convert.ToInt32(random.NextDouble() * 1_000_000));

            n = p * q;
            elementBytes = n.ToByteArray().Length;
            publicKey = 65_537; // coprime with (p-1)(q-1)

            privateKey = findInverse(publicKey, (p - 1) * (q - 1));
        }

        /*public void GenerateBigKey()
        {

        }*/

        private BigInteger findInverse(BigInteger e, BigInteger module)
        {
            // Extended Euclid: 
            // Diofant : ax + by = 1 -> e*x + module*y = 1

            BigInteger r1 = e, r2 = module, q = e / module;
            BigInteger r = r1 - r2 * q;
            BigInteger x1 = 1, x2 = 0, x = 1;

            while (r != 0)
            {
                r1 = r2;
                r2 = r;
                x1 = x2;
                x2 = x;

                q = r1 / r2;
                r = r1 % r2;

                if (r != 0)
                {
                    x = x1 - x2 * q;
                }
            }

            // x0 = x2
            return BigInteger.Abs(x2);
        }

        private BigInteger findGreaterPrime(BigInteger number)
        {
            bool foundPrime = false;
            while(!foundPrime)
            {
                if (number % 2 == 0 || number % 3 == 0 || number % 5 == 0 || number % 7 == 0 || number % 9 == 0)
                {
                    break;
                }

                BigInteger a1 = 11, a2 = 13, a3 = 17, a4 = 19;
                while (a4 < number / 2)
                {
                    if (number % a1 == 0 || number % a2 == 0 || number % a3 == 0 || number % a4 == 0)
                    {
                        foundPrime = true;
                        break;
                    }
                    a1 = a1 + 10;
                    a2 = a2 + 10;
                    a3 = a3 + 10;
                    a4 = a4 + 10;
                }

                if (!foundPrime)
                {
                    number = number + 1;
                }
            }

            return number;
        }

        public void Crypt(String filename, String cryptFilename)
        {
            FileInfo fileInfo = new FileInfo(filename);
            byte info;
            BitArray exponentBits = new BitArray(publicKey.ToByteArray());

            using (var read = new BinaryReader(File.Open(filename, FileMode.Open)))
            {
                
                for (int i = 0; i < fileInfo.Length; i++)
                {
                    info = read.ReadByte();

                    //repeated squaring:
                    
                    bool zero = true, bit;
                    BigInteger p = new BigInteger(1);
                    for (int k = exponentBits.Length - 1; i >= 0; i++)
                    {
                        bit = exponentBits.Get(k);
                        if (zero)
                        {
                            if (!bit)
                            {
                                continue;
                            }
                        }

                        zero = false;
                        p *= p;
                        p = bit ? (p * info) % n : p % n;
                    }

                    using (var write = new BinaryWriter(File.Open(cryptFilename, FileMode.Append)))
                    {
                        byte[] cipherBlock = p.ToByteArray();
                        foreach (var a in cipherBlock)
                        {
                            write.Write(a);
                        }
                        byte append = 0;
                        for (int k = 0; k < elementBytes - cipherBlock.Length; k++)
                        {
                            write.Write(append);
                        }
                    }
                }
            }
        }

        public void Decrypt(String filename, String decryptFilename)
        {
            FileInfo fileInfo = new FileInfo(filename);
            byte[] info = new byte[elementBytes];
            BitArray exponentBits = new BitArray(privateKey.ToByteArray());

            using (var read = new BinaryReader(File.Open(filename, FileMode.Open)))
            {
                for (int i = 0; i < fileInfo.Length; i++)
                {
                    for (int k = 0; k < elementBytes; k++)
                    {
                        info[k] = read.ReadByte();
                    }
                    BigInteger infoInt = new BigInteger(info);

                    //repeated squaring:
                    
                    bool zero = true, bit;
                    BigInteger p = new BigInteger(1);
                    for (int k = exponentBits.Length - 1; i >= 0; i++)
                    {
                        bit = exponentBits.Get(k);
                        if (zero)
                        {
                            if (!bit)
                            {
                                continue;
                            }
                        }

                        zero = false;
                        p *= p;
                        p = bit ? (p * infoInt) % n : p % n;
                    }

                    using (var write = new BinaryWriter(File.Open(decryptFilename, FileMode.Append)))
                    {
                        
                        foreach (var a in p.ToByteArray())
                        {
                            write.Write(a);
                        }

                    }
                }
            }
        }
    }
}
