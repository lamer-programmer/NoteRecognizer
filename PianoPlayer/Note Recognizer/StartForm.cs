using System.Windows.Forms;

namespace Note_Recognizer
{
    class StartForm : Form
    {
        public string Filename { get; }
        public StartForm()
        {
            OpenFileDialog OPF = new OpenFileDialog();
            OPF.Filter = "Файлы wav|*.wav";
            if (OPF.ShowDialog() == DialogResult.OK)
            {
                Filename = OPF.FileName;
            }
        }
    }
}
