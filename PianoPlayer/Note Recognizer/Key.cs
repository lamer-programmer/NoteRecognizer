using System.Drawing;
using Note_Recognizer;

namespace NoteRecognizer
{
    public class Key: Rectangle
    {
        public const int whiteHeight = 24;
        public const int whiteWidth = 20;
        public const int blackHeight = 16;
        public const int blackWidth = 14;
        public const int ypos = 100;
        public static int octave;
        static readonly bool[] octaveIsWhite = new bool[]{
            true,
            false,
            true,
            false,
            true,
            true,
            false,
            true,
            false,
            true,
            false,
            true,
        };
        static readonly int[] octaveXPos = new int[]
        {
            0,
            whiteWidth - blackWidth / 2,
            whiteWidth,
            whiteWidth * 2 - blackWidth / 2,
            whiteWidth * 2,
            whiteWidth * 3,
            whiteWidth * 4 - blackWidth / 2,
            whiteWidth * 4,
            whiteWidth * 5 - blackWidth / 2,
            whiteWidth * 5,
            whiteWidth * 6 - blackWidth / 2,
            whiteWidth * 6,
        };
        static readonly Brush[] octaveColor = new Brush[]
        {
            Brushes.Red,
            Brushes.OrangeRed,
            Brushes.Orange,
            Brushes.Yellow,
            Brushes.YellowGreen,
            Brushes.GreenYellow,
            Brushes.Green,
            Brushes.Cyan,
            Brushes.Blue,
            Brushes.BlueViolet,
            Brushes.Violet,
            Brushes.Magenta
        };

        WMPLib.WindowsMediaPlayer wplayer;


        public bool isWhite;
        public Brush color;
        public string frequencySound;

        public Key(int index, double scale)
        {
            octave = index / 12;
            var tone = index % 12;

            var d = 2;
            var octaveSoundString = new string[]
            {
                $"C{octave+d}",
                $"Db{octave+d}",
                $"D{octave+d}",
                $"Eb{octave+d}",
                $"E{octave+d}",
                $"F{octave+d}",
                $"Gb{octave+d}",
                $"G{octave+d}",
                $"Ab{octave+d}",
                $"A{octave+d}",
                $"Bb{octave+d}",
                $"B{octave+d}"
            };

            frequencySound = octaveSoundString[tone];
            wplayer = new WMPLib.WindowsMediaPlayer();
            //wplayer.URL = @"C:\Users\Пользователь\Desktop\Note Recognizer\piano-mp3\" + frequencySound + ".mp3";
            color = octaveColor[tone];

            Xpos = (int)(octave * 7 * whiteWidth + octaveXPos[tone] * scale);
            Ypos = ypos;

            isWhite = octaveIsWhite[tone];
            width = (int)((isWhite ? whiteWidth : blackWidth) * scale);
            height = isWhite ? whiteHeight : blackHeight;
        }

        public void PlaySound()
        {
            var rootDir = DirHelper.GetRootDirPath();
            wplayer.URL = rootDir + "piano-mp3\\" + frequencySound + ".mp3";
            wplayer.controls.play();
        }

        string GetString()
        {
            return "";
        }
    }
}
