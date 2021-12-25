using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NoteRecognizer
{
    public class Rectangle
    {
        public int height;
        public int width;
        public int Xpos;
        public int Ypos;

        public System.Drawing.Rectangle toRectangle()
        {
            return new System.Drawing.Rectangle(Xpos, Ypos, width, height);
        }
    }
}
