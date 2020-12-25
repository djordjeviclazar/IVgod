using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileFunctions
{
    class Program
    {
        static void Main(string[] args)
        {
            //Stopwatch stopwatch = new Stopwatch();
            //byte[] p;

            //stopwatch.Start();
            //p = FileFunctions.ReadBytes("Testfiles/A1B1PlainText1.ppt");
            //FileFunctions.WriteBytes("Testfiles/A1B1PlainText1Copy.ppt", p);
            //stopwatch.Stop();
            //Console.WriteLine("Time for Byte operations: " + stopwatch.Elapsed);


            //stopwatch.Restart();
            //p = FileFunctions.ReadAllBytes("Testfiles/A1B1PlainText1.ppt");
            //FileFunctions.WriteAllBytes("Testfiles/A1B1PlainText1Copy2.ppt", p);
            //stopwatch.Stop();
            //Console.WriteLine("Time for AllByte operations: " + stopwatch.Elapsed);

            //Console.ReadLine();

            using(BinaryReader r = new BinaryReader(File.OpenRead("Testfiles/New Text Document.txt")))
            {
                byte[] b = r.ReadBytes(500);
                Console.WriteLine(b.Length);
            }

            Console.ReadLine();
        }
    }
}
