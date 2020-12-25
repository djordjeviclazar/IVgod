using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileFunctions
{
    public class FileFunctions
    {
        public static byte[] ReadBytes(String filename)
        {
            FileInfo fileInfo = new FileInfo(filename);
            byte[] bytes = new byte[fileInfo.Length];

            using (BinaryReader stream = new BinaryReader(File.Open(filename, FileMode.Open)))
            {
                for (int i = 0; i < bytes.Length; i++)
                {
                    bytes[i] = stream.ReadByte();
                }
            }

            return bytes;
        }

        public static void WriteBytes(String filename, byte[] info)
        {
            using (BinaryWriter stream = new BinaryWriter(File.Open(filename, FileMode.OpenOrCreate)))
            {
                foreach (var a in info)
                {
                    stream.Write(a);
                }
            }
        }

        public static byte[] ReadAllBytes(String filename)
        {

            byte[] bytes = File.ReadAllBytes(filename);

            return bytes;
        }

        public static void WriteAllBytes(String filename, byte[] info)
        {
            File.WriteAllBytes(filename, info);
        }

        public static byte[] ReadAllBytesBmp(String filename, out byte[] header) // B2
        {
            FileInfo fileInfo = new FileInfo(filename);
            byte[] bytes = new byte[14], head, result;

            using (BinaryReader stream = new BinaryReader(File.Open(filename, FileMode.Open)))
            {
                for (int i = 0; i < 14; i++)
                {
                    bytes[i] = stream.ReadByte();
                }
                int pos = bytes[10] + 256 * (bytes[11] + 256 * (bytes[12] + 256 * bytes[13]));

                head = new byte[pos];
                result = new byte[fileInfo.Length - pos];

                int k = 0;
                foreach (var a in bytes) 
                { 
                    head[k++] = a;
                }
                for (int i = 14; i < pos; i++)
                {
                    head[i] = stream.ReadByte();
                }
                for (int i = 0; i < fileInfo.Length - pos; i++)
                {
                    result[i] = stream.ReadByte();
                }
            }

            header = head;
            return result;
        }

        public static void WriteAllBytesBmp(String filename, byte[] info, byte[] head) // B2
        {
            // File.WriteAllBytes(filename, head);

            using (BinaryWriter stream = new BinaryWriter(File.Open(filename, FileMode.OpenOrCreate)))
            {
                foreach(var a in head)
                {
                    stream.Write(a);
                }

                foreach (var a in info)
                {
                    stream.Write(a);
                }
            }
        }

        public static String ReadAllText(String filename)
        {
            return File.ReadAllText(filename);
        }

        public static void WriteAllText(String filename, String text)
        {
            File.WriteAllText(filename, text);
        }

        public static List<char> ReadAllLettersBifid(String filename)
        {
            List<char> letters = new List<char>();
            String text = File.ReadAllText(filename);

            char current;
            foreach(var a in text)
            {
                if (a.Equals('j') || a.Equals('J'))
                {
                    current = 'i';
                    letters.Add(current);
                }
                else
                {
                    if (Char.IsLetter(a))
                    {
                        current = Char.ToLower(a);
                        letters.Add(current);
                    }
                }
            }

            return letters;
        }

        // A2 helpers:
        public static void WriteAllLettersBifid(String filename, char[] letters)
        {
            File.WriteAllText(filename, new string(letters));
        }

        public static void WriteAllLettersBifid(String filename, byte[] letters)
        {
            using (BinaryWriter stream = new BinaryWriter(File.Open(filename, FileMode.OpenOrCreate)))
            {
                foreach (var a in letters)
                {
                    stream.Write(a);
                }
            }
        }
    }
}
