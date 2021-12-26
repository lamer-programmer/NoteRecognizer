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
