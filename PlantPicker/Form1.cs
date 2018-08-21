using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace PlantPicker
{
    public partial class Form1 : Form
    {
        //array of bools indicating which images have been selected 
        bool[] selectedFerns = new bool[20];

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            loadFerns();
        }

        private void loadFerns()
        {
            //always start with ferns selected
            string[] lines = File.ReadAllLines(@"FernData.txt");
            lines[0] = 0.ToString() + " ";
            File.WriteAllLines(@"FernData.txt", lines);

            //images have to be loaded into a temp file then re assigned or else the app will stop
            //  the command line program from changing the image files as they are still in use
            Image[] buttonImages = new Image[20];

            for (int i = 0; i < buttonImages.Length; i++)
            {
                using (var bmpTemp = new Bitmap("bf" + i + ".bmp"))
                {
                    //the images need to be made to be half the size of the buttons to fit properly
                    //this makes no sense and took me too long to figure out
                    //the "stretch" property that fits the image to the size also does not work
                    buttonImages[i] = new Bitmap(bmpTemp, new Size(100,100));
                }
            }

            //then assign the temp image files to the actual image property of the buttons
            button1.Image = buttonImages[0];
            button2.Image = buttonImages[1];
            button3.Image = buttonImages[2];
            button4.Image = buttonImages[3];
            button5.Image = buttonImages[4];
            button6.Image = buttonImages[5];
            button7.Image = buttonImages[6];
            button8.Image = buttonImages[7];
            button9.Image = buttonImages[8];
            button10.Image = buttonImages[9];
            button11.Image = buttonImages[10];
            button12.Image = buttonImages[11];
            button13.Image = buttonImages[12];
            button14.Image = buttonImages[13];
            button15.Image = buttonImages[14];
            button16.Image = buttonImages[15];
            button17.Image = buttonImages[16];
            button18.Image = buttonImages[17];
            button19.Image = buttonImages[18];
            button20.Image = buttonImages[19];
        }

        private void loadTrees()
        {
            //always start with ferns selected
            string[] lines = File.ReadAllLines(@"TreeData.txt");
            lines[0] = 0.ToString() + " ";
            File.WriteAllLines(@"TreeData.txt", lines);

            //images have to be loaded into a temp file then re assigned or else the app will stop
            //  the command line program from changing the image files as they are still in use
            Image[] buttonImages = new Image[20];

            for (int i = 0; i < buttonImages.Length; i++)
            {
                using (var bmpTemp = new Bitmap("tree" + i + ".bmp"))
                {
                    //the images need to be made to be half the size of the buttons to fit properly
                    //this makes no sense and took me too long to figure out
                    //the "stretch" property that fits the image to the size also does not work
                    buttonImages[i] = new Bitmap(bmpTemp, new Size(100, 100));
                }
            }

            //then assign the temp image files to the actual image property of the buttons
            button1.Image = buttonImages[0];
            button2.Image = buttonImages[1];
            button3.Image = buttonImages[2];
            button4.Image = buttonImages[3];
            button5.Image = buttonImages[4];
            button6.Image = buttonImages[5];
            button7.Image = buttonImages[6];
            button8.Image = buttonImages[7];
            button9.Image = buttonImages[8];
            button10.Image = buttonImages[9];
            button11.Image = buttonImages[10];
            button12.Image = buttonImages[11];
            button13.Image = buttonImages[12];
            button14.Image = buttonImages[13];
            button15.Image = buttonImages[14];
            button16.Image = buttonImages[15];
            button17.Image = buttonImages[16];
            button18.Image = buttonImages[17];
            button19.Image = buttonImages[18];
            button20.Image = buttonImages[19];
        }


        //On each button click it "selects" the fern, adding the info to the selectedFerns array
        //if the fern was selected it deselects it instead (and again updates the array
        //a tick mark is put on the button to indicate that it has been selected
        //this code is the same for buttons 1 though 20
        private void button1_Click(object sender, EventArgs e)
        {
            if (selectedFerns[0])
            {
                button1.Text = "";
                selectedFerns[0] = false;
            }
            else
            {
                button1.Text = "✔";
                selectedFerns[0] = true;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (selectedFerns[1])
            {
                button2.Text = "";
                selectedFerns[1] = false;
            }
            else
            {
                button2.Text = "✔";
                selectedFerns[1] = true;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (selectedFerns[2])
            {
                button3.Text = "";
                selectedFerns[2] = false;
            }
            else
            {
                button3.Text = "✔";
                selectedFerns[2] = true;
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (selectedFerns[3])
            {
                button4.Text = "";
                selectedFerns[3] = false;
            }
            else
            {
                button4.Text = "✔";
                selectedFerns[3] = true;
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (selectedFerns[4])
            {
                button5.Text = "";
                selectedFerns[4] = false;
            }
            else
            {
                button5.Text = "✔";
                selectedFerns[4] = true;
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (selectedFerns[5])
            {
                button6.Text = "";
                selectedFerns[5] = false;
            }
            else
            {
                button6.Text = "✔";
                selectedFerns[5] = true;
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (selectedFerns[6])
            {
                button7.Text = "";
                selectedFerns[6] = false;
            }
            else
            {
                button7.Text = "✔";
                selectedFerns[6] = true;
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (selectedFerns[7])
            {
                button8.Text = "";
                selectedFerns[7] = false;
            }
            else
            {
                button8.Text = "✔";
                selectedFerns[7] = true;
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (selectedFerns[8])
            {
                button9.Text = "";
                selectedFerns[8] = false;
            }
            else
            {
                button9.Text = "✔";
                selectedFerns[8] = true;
            }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (selectedFerns[9])
            {
                button10.Text = "";
                selectedFerns[9] = false;
            }
            else
            {
                button10.Text = "✔";
                selectedFerns[9] = true;
            }
        }

        private void button11_Click(object sender, EventArgs e)
        {
            if (selectedFerns[10])
            {
                button11.Text = "";
                selectedFerns[10] = false;
            }
            else
            {
                button11.Text = "✔";
                selectedFerns[10] = true;
            }
        }

        private void button12_Click(object sender, EventArgs e)
        {
            if (selectedFerns[11])
            {
                button12.Text = "";
                selectedFerns[11] = false;
            }
            else
            {
                button12.Text = "✔";
                selectedFerns[11] = true;
            }
        }

        private void button13_Click(object sender, EventArgs e)
        {
            if (selectedFerns[12])
            {
                button13.Text = "";
                selectedFerns[12] = false;
            }
            else
            {
                button13.Text = "✔";
                selectedFerns[12] = true;
            }
        }

        private void button14_Click(object sender, EventArgs e)
        {
            if (selectedFerns[13])
            {
                button14.Text = "";
                selectedFerns[13] = false;
            }
            else
            {
                button14.Text = "✔";
                selectedFerns[13] = true;
            }
        }

        private void button15_Click(object sender, EventArgs e)
        {
            if (selectedFerns[14])
            {
                button15.Text = "";
                selectedFerns[14] = false;
            }
            else
            {
                button15.Text = "✔";
                selectedFerns[14] = true;
            }
        }

        private void button16_Click(object sender, EventArgs e)
        {
            if (selectedFerns[15])
            {
                button16.Text = "";
                selectedFerns[15] = false;
            }
            else
            {
                button16.Text = "✔";
                selectedFerns[15] = true;
            }
        }

        private void button17_Click(object sender, EventArgs e)
        {
            if (selectedFerns[16])
            {
                button17.Text = "";
                selectedFerns[16] = false;
            }
            else
            {
                button17.Text = "✔";
                selectedFerns[16] = true;
            }
        }

        private void button18_Click(object sender, EventArgs e)
        {
            if (selectedFerns[17])
            {
                button18.Text = "";
                selectedFerns[17] = false;
            }
            else
            {
                button18.Text = "✔";
                selectedFerns[17] = true;
            }
        }

        private void button19_Click(object sender, EventArgs e)
        {
            if (selectedFerns[18])
            {
                button19.Text = "";
                selectedFerns[18] = false;
            }
            else
            {
                button19.Text = "✔";
                selectedFerns[18] = true;
            }
        }

        private void button20_Click(object sender, EventArgs e)
        {
            if (selectedFerns[19])
            {
                button20.Text = "";
                selectedFerns[19] = false;
            }
            else
            {
                button20.Text = "✔";
                selectedFerns[19] = true;
            }
        }

        //Button 21 is the Generate new ferns button
        private void button21_Click(object sender, EventArgs e)
        {
            //to edit part of a text file you must read in the entire file, edit the parts you want
            //then write the whole thing back to the same file
            string[] lines = File.ReadAllLines(@"FernData.txt");
            string selectLine = "";

            //this goes though the selectedFerns array
            for (int i = 0; i < selectedFerns.Length; i++)
            {
                //if the selectedFern is true add 1 to the string, if false add 0
                if (selectedFerns[i])
                {
                    selectLine += "1 ";
                }
                else
                {
                    selectLine += "0 ";
                }
                //the next line resets all the selections to false
                //as there will be a new set generated next
                selectedFerns[i] = false;
            }

            //reset all the text on the buttons on screen
            foreach (Button btn in Controls.OfType<Button>())
            {
                btn.Text = "";
            }
            button21.Text = "Generate!"; //except the text on this button
            button22.Text = "Save As...";
            lines[1] = selectLine; //replace the first line with the new string (of selected images)
            File.WriteAllLines(@"FernData.txt", lines); //write all the data back to the file

            //run the fern generating program and wait for it to complete
            var fernGenerator = Process.Start(@"Fern1.exe");
            fernGenerator.WaitForExit();

            //reload the images on the buttons so you can start again
            loadFerns();
        }

        private void button22_Click(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButton1.Checked)
            {
                string[] lines = File.ReadAllLines(@"FernData.txt");
                lines[0] = 0.ToString() + " ";
                File.WriteAllLines(@"FernData.txt", lines);

                loadFerns();
            }
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            string[] lines = File.ReadAllLines(@"FernData.txt");
            lines[0] = 1.ToString() + " ";
            File.WriteAllLines(@"FernData.txt", lines);

            loadTrees();
        }
    }
}
