using System.Collections.Generic;
using NoteRecognizer;
using NUnit.Framework;

namespace NUnit.Tests
{
    [TestFixture]
    public class TestParser
    {
        [Test]
        public void TestParsedWell()
        {
            var lines = new string[] { "1", "1 2", "3" };
            var actual = Parser.ParseMelody(lines);
            var expected = new List<Note>();
            expected.Add(new Note(0, 1));
            expected.Add(new Note(1, 1));
            expected.Add(new Note(1, 2));
            expected.Add(new Note(2, 3));
            Assert.AreEqual(expected.Count, actual.Count);
            for (var i = 0; i < expected.Count; i++)
            {
                Assert.That(expected[i] == actual[i]);
            }
        }

    }
}
