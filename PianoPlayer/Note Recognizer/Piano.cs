using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NoteRecognizer
{
    public class Piano
    {
        public Key[] keys;

        public Piano(int keyCount, double scale) {
            keys = new Key[keyCount];
            for (int i = 0; i < keyCount; i++)
            {
                keys[i] = new Key(i, scale);
            }
        }
    }
}
