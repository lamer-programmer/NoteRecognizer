using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NoteRecognizer
{
    public class Note
    {
        public int start;
        public int key;

        public Note(int start, int key)
        {
            this.start = start;
            this.key = key;
        }

        public static bool operator ==(Note note1, Note note2)
        {
            return note1.key == note2.key && note1.start == note2.start;
        }
        public static bool operator !=(Note note1, Note note2)
        {
            return note1.key != note2.key || note1.start != note2.start;
        }
    }
}
