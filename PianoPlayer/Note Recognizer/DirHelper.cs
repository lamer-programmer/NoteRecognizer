using System.IO;

namespace Note_Recognizer
{
    internal static class DirHelper
    {
        public static string GetRootDirPath()
        {
            var folderName = "PianoPlayer";
            var path = Directory.GetCurrentDirectory();
            var first = path.IndexOf(folderName) + folderName.Length;
            path = path.Substring(0, first);
            return path + "\\";
        }

        public static string GetExePath()
        {
            var folderName = "NoteRecognizer";
            var path = Directory.GetCurrentDirectory();
            var first = path.IndexOf(folderName) + folderName.Length;
            path = path.Substring(0, first);
            return path + "\\x64\\Debug\\NoteRecognizer.exe";
        }
        public static string GetTxtPath()
        {
            var folderName = "NoteRecognizer";
            var path = Directory.GetCurrentDirectory();
            var first = path.IndexOf(folderName) + folderName.Length;
            path = path.Substring(0, first);
            return path + "\\NoteRecognizer\\Notes.txt";
        }
    }
}
