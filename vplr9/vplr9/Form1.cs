using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace vplr9
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void domainUpDown1_SelectedItemChanged(object sender, EventArgs e)
        {
            comboBox1.Text = "";
            if (domainUpDown1.SelectedIndex == 0)
            {
                comboBox1.Items.Clear();
                comboBox1.Items.AddRange(new string[] { "ПРИ", "ИВТ", "МОА" });
            }
            if (domainUpDown1.SelectedIndex == 1)
            {
                comboBox1.Items.Clear();
                comboBox1.Items.AddRange(new string[] { "ТМО", "КТО", "УТС" });
            }
            if (domainUpDown1.SelectedIndex == 2)
            {
                comboBox1.Items.Clear();
                comboBox1.Items.AddRange(new string[] { "ЭК", "ПИ", "МНТ" });
            }
        }

        private void domainUpDown2_SelectedItemChanged_1(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            comboBox2.Text = "";
            if (domainUpDown2.SelectedIndex == 0)
            {
                comboBox2.Items.Clear();
                comboBox2.Items.AddRange(new string[] { "ПРИ", "ИВТ", "МОА" });
            }
            if (domainUpDown2.SelectedIndex == 1)
            {
                comboBox2.Items.Clear();
                comboBox2.Items.AddRange(new string[] { "ТМО", "КТО", "УТС" });
            }
            if (domainUpDown2.SelectedIndex == 2)
            {
                comboBox2.Items.Clear();
                comboBox2.Items.AddRange(new string[] { "ЭК", "ПИ", "МНТ" });
            }
        }

        string[] subj;

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (domainUpDown2.SelectedIndex == 0)
            {
                if (comboBox2.SelectedIndex == 0)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "САОД", "ООП", "Вычислительная математика", "Визуальное программирование" };
                    listBox1.Items.AddRange(subj);
                }
                if (comboBox2.SelectedIndex == 1)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "ООП", "Вычислительная математика" };
                    listBox1.Items.AddRange(subj);
                }
                if (comboBox2.SelectedIndex == 2)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "САОД", "ООП", "Вычислительная математика" };
                    listBox1.Items.AddRange(subj);
                }
            }
            if (domainUpDown2.SelectedIndex == 1)
            {
                if (comboBox2.SelectedIndex == 0)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "Физика", "Сопромат", "Матанализ", "Философия" };
                    listBox1.Items.AddRange(subj);
                }
                if (comboBox2.SelectedIndex == 1)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "Матанализ", "Философия" };
                    listBox1.Items.AddRange(subj);
                }
                if (comboBox2.SelectedIndex == 2)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "Физика", "Сопромат", "Философия" };
                    listBox1.Items.AddRange(subj);
                }
            }
            if (domainUpDown2.SelectedIndex == 2)
            {
                if (comboBox2.SelectedIndex == 0)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "Экономика", "Математика", "Философия" };
                    listBox1.Items.AddRange(subj);
                }
                if (comboBox2.SelectedIndex == 1)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "Экономика", "Математика", "Философия", "Программирование" };
                    listBox1.Items.AddRange(subj);
                }
                if (comboBox2.SelectedIndex == 2)
                {
                    listBox1.Items.Clear();
                    subj = new string[] { "Экономика", "Математика" };
                    listBox1.Items.AddRange(subj);
                }
            }
        }
    }
}