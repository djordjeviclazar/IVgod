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
        static byte[] ReadBytes(String filename)
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

        static void WriteBytes(String filename, byte[] info)
        {
            using (BinaryWriter stream = new BinaryWriter(File.Open(filename, FileMode.OpenOrCreate)))
            {
                foreach (var a in info)
                {
                    stream.Write(a);
                }
            }
        }
    }
}
