using System;
using System.Windows.Forms;
using System.Diagnostics;

namespace Note_Recognizer
{
    internal static class Program
    {
        static void LaunchExe(string wavPath)
        {
            var exePath = DirHelper.GetExePath();
            Process.Start(exePath, wavPath)?.WaitForExit();
        }

        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            var startForm = new StartForm();
            var pathToWav = startForm.Filename;

            LaunchExe(pathToWav);

            var txtFilename = DirHelper.GetTxtPath();

            Application.Run(new PianoForm(txtFilename));
        }
    }
}
