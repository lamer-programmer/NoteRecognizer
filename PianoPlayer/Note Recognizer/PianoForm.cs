using NoteRecognizer;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace Note_Recognizer
{
    public partial class PianoForm : Form
    {
        private Piano piano;
        private int tickCount;
        private List<Note> notes;
        private Timer timer;
        //WMPLib.WindowsMediaPlayer wplayer;

        //C D EF G A BC
        //0123456789012
        public PianoForm(string fileName)
        {
            var lines = System.IO.File.ReadAllLines(fileName);
            notes = Parser.ParseMelody(lines);

            var keyCount = 48;
            //var screenWidth = Screen.PrimaryScreen.WorkingArea.Size.Width;
            //var width = keyCount * Key.whiteWidth;
            var scale = 1;//screenWidth * 1.0 / width;

            piano = new Piano(keyCount, scale);

            ClientSize = new Size(
                piano.keys.Length * 7 / 12 * Key.whiteWidth,
                Key.ypos + Key.whiteHeight
            );

            //wplayer = new WMPLib.WindowsMediaPlayer();

            timer = new Timer();
            timer.Interval = 12;
            timer.Tick += TimerTick;
            timer.Start();
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            Text = "";
            DoubleBuffered = true;
        }

        private void DrawNote(Note note, Graphics graphics)
        {
            var noteHeight = 20;

            var key = piano.keys[note.key];
            var y = tickCount - (note.start - 1) * noteHeight;
            var yprev = (tickCount - 1) - (note.start - 1) * noteHeight;
            var x = key.Xpos;
            var w = key.width;
            var h = noteHeight;
            graphics.FillRectangle(key.color, x + 1, y, w - 2, h);

            if (y + h >= Key.ypos && yprev + h < Key.ypos)
            {
                key.PlaySound();
            }
            //System.Console.Beep((int)key.frequency, noteHeight * timer.Interval);
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            foreach (var note in notes)
            {
                DrawNote(note, e.Graphics);
            }

            foreach (var key in piano.keys)
            {
                if (!key.isWhite)
                    continue;
                e.Graphics.FillRectangle(
                    Brushes.White,
                    key.Xpos + 1,
                    key.Ypos + 1,
                    key.width - 2,
                    key.height - 2
                );
            }
            
            foreach (var key in piano.keys)
            {
                if (key.isWhite)
                    continue;
                e.Graphics.FillRectangle(
                    Brushes.Black,
                    key.Xpos + 1,
                    key.Ypos + 1,
                    key.width - 2,
                    key.height - 2
                );
            }
        }

        private void TimerTick(object sender, EventArgs args)
        {
            tickCount++;
            Invalidate();
        }
    }
}
