using System.Collections.Generic;

namespace NoteRecognizer
{
    public static class Parser
    {
        public static List<Note> ParseMelody(string[] lines)
        {
            var notes = new List<Note>();
            for (var i = 0; i < lines.Length; i++)
            {
                var line = lines[i].Trim();
                if (line == "")
                    continue;
                var parts = line.Split(' ');
                foreach (var part in parts)
                {
                    notes.Add(new Note(i, int.Parse(part)));
                }
            }
            return notes;
        }

    }
}
