using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using SharpGL.SceneGraph;
using SharpGL;
using SharpGL.WPF;
using SharpGL.SceneGraph.Assets;
//using WinForms = System.Windows.Forms;


namespace Metal_Slug_Map_Editor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="MainWindow"/> class.
        /// </summary>
        /// 


        #region variables

        int status=0;

        private double zoom = 1;
        private System.Windows.Point center;
        private System.Windows.Point mousePoint;
        private System.Windows.Point rightButtonPoint;

        uint[] textures = new uint[10];
        BitmapData[] data = new BitmapData[10];
        string dir;

        public class Image
        {
            public int imgNum;
            public double depth;
            public double x;
            public double y;
            public int width;
            public int height;
        }

        List<Image> imgList = new List<Image>();

        List<Image> BGList = new List<Image>(), FGList = new List<Image>(), RearList = new List<Image>();

        #endregion

        #region Constructor
        public MainWindow()
        {
            dir = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            InitializeComponent();
            openGLControl.MouseMove += openGLControl_MouseMove;// System.Windows.Input.MouseEventHandler( this.openGLControl_MouseMove);
            openGLControl.MouseWheel += openGLControl_MouseWheel;
            openGLControl.MouseLeftButtonDown += openGLControl_MouseLeftButtonDown;
            openGLControl.MouseRightButtonDown += openGLControl_MouseRightButtonDown;
            openGLControl.MouseRightButtonUp += openGLControl_MouseRightButtonUp;
            tvMapLoad();
        }
        #endregion

        #region TreeViewLoader
        
        private void tvMapLoad()
        {
            TreeViewItem treeItem = null;
            String str;            

            string file = dir + @"\Data\Map.txt";
            StreamReader sr = new StreamReader(file);
            int c;
            int cnt = 0;
            treeItem = GetTreeView("Background", Colors.Green);
            str = sr.ReadLine();
            c = int.Parse(str);
            for (int i = 0; i < c; i++)
            {
                str = sr.ReadLine();
                treeItem.Items.Add(GetTreeView(str,cnt*10));
                cnt++;
            }
            tvMap.Items.Add(treeItem);

            treeItem = GetTreeView("Foreground", Colors.Green);
            str = sr.ReadLine();
            c = int.Parse(str);
            for (int i = 0; i < c; i++)
            {
                str = sr.ReadLine();
                treeItem.Items.Add(GetTreeView(str,cnt*10+1));
                cnt++;
            }
            tvMap.Items.Add(treeItem);

            treeItem = GetTreeView("Front", Colors.Green);
            str = sr.ReadLine();
            c = int.Parse(str);
            for (int i = 0; i < c; i++)
            {
                str = sr.ReadLine();
                treeItem.Items.Add(GetTreeView(str,cnt*10+2));
                cnt++;
            }
            tvMap.Items.Add(treeItem);

        }

        private void tvMap_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            var item = e.NewValue as TreeViewItem;
            lFileName.Content = item.Header.ToString();

            status = int.Parse(item.Tag.ToString()+1);
            
        }

        private TreeViewItem GetTreeView(string text,int tag)
        {
            TreeViewItem item = new TreeViewItem();

            item.IsExpanded = true;
            
            // assign stack to header
            item.Header = text;
            item.Tag = tag;
            return item;

        }

        private TreeViewItem GetTreeView(string text, System.Windows.Media.Color boxColor)
        {
            TreeViewItem item = new TreeViewItem();
            item.Focusable = false;
            item.IsExpanded = true;

            // create stack panel
            StackPanel stack = new StackPanel();
            stack.Orientation = Orientation.Horizontal;

            // create Image

            Border border = new Border();
            border.Width = 8;
            border.Height = 12;
            border.Background = new SolidColorBrush(boxColor);

            // Label
            Label lbl = new Label();
            lbl.Content = text;

            stack.Children.Add(border);
            stack.Children.Add(lbl);

            //item.HeaderTemplate.ad
            item.Header = stack;
            return item;

        }

        #endregion

        #region CamEvent
        private void tvCam_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int item = tvCam.SelectedIndex;
 //           var item = e.Source as ListViewItem;
            //item.Content

            lFileName.Content = item;
            status = 1;
        }
        #endregion

        #region OpenGL
        /// <summary>
        /// Handles the OpenGLDraw event of the openGLControl1 control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="args">The <see cref="SharpGL.SceneGraph.OpenGLEventArgs"/> instance containing the event data.</param>
        private void openGLControl_OpenGLDraw(object sender, OpenGLEventArgs args)
        {
            int w = (int)openGLControl.ActualWidth / 2, h = (int)openGLControl.ActualHeight / 2;

            //  Get the OpenGL instance.
            var gl = args.OpenGL;
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);

            gl.PointSize(2.0f);

            lbZoom.Content = ((mousePoint.X - w) * zoom + center.X) + "," + ((-mousePoint.Y + h) * zoom+ center.Y);


            gl.Color(1f, 1f, 1f);
            
            foreach (var img in BGList)
            {
                gl.BindTexture(OpenGL.GL_TEXTURE_2D, textures[img.imgNum]);
                gl.Begin(OpenGL.GL_QUADS);
                gl.TexCoord(0.0f, 1.0f); gl.Vertex(img.x, img.y - img.height, 0);
                gl.TexCoord(1.0f, 1.0f); gl.Vertex(img.x + img.width, img.y - img.height, 0);
                gl.TexCoord(1.0f, 0.0f); gl.Vertex(img.x + img.width, img.y, 0);
                gl.TexCoord(0.0f, 0.0f); gl.Vertex(img.x, img.y, 0);
                gl.End();
            }

            foreach (var img in FGList)
            {
                gl.BindTexture(OpenGL.GL_TEXTURE_2D, textures[img.imgNum]);
                gl.Begin(OpenGL.GL_QUADS);
                gl.TexCoord(0.0f, 1.0f); gl.Vertex(img.x, img.y - img.height, 0);
                gl.TexCoord(1.0f, 1.0f); gl.Vertex(img.x + img.width, img.y - img.height, 0);
                gl.TexCoord(1.0f, 0.0f); gl.Vertex(img.x + img.width, img.y, 0);
                gl.TexCoord(0.0f, 0.0f); gl.Vertex(img.x, img.y, 0);
                gl.End();
            }

            foreach (var img in RearList)
            {
                gl.BindTexture(OpenGL.GL_TEXTURE_2D, textures[img.imgNum]);
                gl.Begin(OpenGL.GL_QUADS);
                gl.TexCoord(0.0f, 1.0f); gl.Vertex(img.x, img.y - img.height, 0);
                gl.TexCoord(1.0f, 1.0f); gl.Vertex(img.x + img.width, img.y - img.height, 0);
                gl.TexCoord(1.0f, 0.0f); gl.Vertex(img.x + img.width, img.y, 0);
                gl.TexCoord(0.0f, 0.0f); gl.Vertex(img.x, img.y, 0);
                gl.End();
            }

            if (status % 10 == 1)
            {
                System.Windows.Point trueMouse = new System.Windows.Point();

                trueMouse.X=(int)((mousePoint.X - w) * zoom + center.X);
                trueMouse.Y=(int)((-mousePoint.Y + h) * zoom + center.Y);

                gl.BindTexture(OpenGL.GL_TEXTURE_2D, textures[status/100]);
                gl.Begin(OpenGL.GL_POINTS);
                gl.Color(1f, 1f, 1f,0.6f);
                gl.Begin(OpenGL.GL_QUADS);
                gl.TexCoord(0.0f, 1.0f); gl.Vertex(trueMouse.X, trueMouse.Y - data[status / 100].Height , 0);
                gl.TexCoord(1.0f, 1.0f); gl.Vertex(trueMouse.X + data[status / 100].Width, trueMouse.Y - data[status / 100].Height, 0);
                gl.TexCoord(1.0f, 0.0f); gl.Vertex(trueMouse.X + data[status/100].Width, trueMouse.Y, 0);
                gl.TexCoord(0.0f, 0.0f); gl.Vertex(trueMouse.X, trueMouse.Y, 0);
                gl.End();
            }

        }

        private void openGLControl_OpenGLInitialized(object sender, OpenGLEventArgs args)
        {
            //  TODO: Initialise OpenGL here.

            //  Get the OpenGL object.
            OpenGL gl = openGLControl.OpenGL;

            //  Set the clear color.
            gl.ClearColor(0, 0, 0, 0);
            gl.Enable(OpenGL.GL_BLEND);
            gl.Enable(OpenGL.GL_TEXTURE_2D);
            gl.BlendFunc(OpenGL.GL_SRC_ALPHA, OpenGL.GL_ONE_MINUS_SRC_ALPHA);
            gl.Hint(HintTarget.PerspectiveCorrection, HintMode.Nicest);


            //////////Texture Load
            gl.GenTextures(10,textures);

            string str, file = dir + @"\Data\Map.txt";
            StreamReader sr = new StreamReader(file);
            int c,cnt=0;
            
            
            for (int i = 0; i < 3; i++)
            {
                str = sr.ReadLine();
                c = int.Parse(str);
                for (int j=0; j < c;j++ )
                {
                    str = sr.ReadLine();
                    gl.BindTexture(OpenGL.GL_TEXTURE_2D, textures[cnt]);

                    file = dir + @"\Image\" + str + ".png";
                    Bitmap bitmap = new Bitmap(file);

                    bitmap.MakeTransparent(System.Drawing.Color.Magenta);

                    data[cnt] = bitmap.LockBits(new System.Drawing.Rectangle(0, 0, bitmap.Width, bitmap.Height),
                        ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb);


                    gl.TexImage2D(OpenGL.GL_TEXTURE_2D, 0, (int)OpenGL.GL_RGBA, data[cnt].Width, data[cnt].Height, 0,
                        OpenGL.GL_BGRA, OpenGL.GL_UNSIGNED_BYTE, data[cnt].Scan0);

                    bitmap.UnlockBits(data[cnt]);
                    bitmap.Dispose();

                    gl.TexParameter(OpenGL.GL_TEXTURE_2D, OpenGL.GL_TEXTURE_MIN_FILTER, OpenGL.GL_LINEAR); // Required for TexImage2D
                    gl.TexParameter(OpenGL.GL_TEXTURE_2D, OpenGL.GL_TEXTURE_MAG_FILTER, OpenGL.GL_LINEAR); // Required for TexImage2D
                    cnt++;
                }
            }
            
        }

        private void openGLControl_Resized(object sender, OpenGLEventArgs args)
        {
            //  TODO: Set the projection matrix here.

            //  Get the OpenGL object.
            OpenGL gl = openGLControl.OpenGL;

            int w = (int)openGLControl.ActualWidth / 2, h = (int)openGLControl.ActualHeight / 2;

            gl.Viewport(-w, w, -h, h);
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadIdentity();
            gl.Ortho2D(-w * zoom + center.X, w * zoom + center.X,
                -h * zoom + center.Y, h * zoom + center.Y);

        }

        private void openGLControl_MouseMove(object sender, MouseEventArgs e)
        {
            mousePoint = e.GetPosition(openGLControl); // Position relative to sharp GL control

            lbSize.Content = mousePoint.X + "," + mousePoint.Y;

            if (rightButtonPoint.X != 0.0)
            {

                OpenGL gl = openGLControl.OpenGL;

                int w = (int)openGLControl.ActualWidth / 2, h = (int)openGLControl.ActualHeight / 2;

                gl.Viewport(-w, w, -h, h);
                gl.MatrixMode(OpenGL.GL_PROJECTION);
                gl.LoadIdentity();
                gl.Ortho2D(-w * zoom + center.X - (mousePoint.X - rightButtonPoint.X) * zoom, w * zoom + center.X - (mousePoint.X - rightButtonPoint.X) *  zoom,
                    -h * zoom + center.Y + (mousePoint.Y - rightButtonPoint.Y) * zoom, h * zoom + center.Y + (mousePoint.Y - rightButtonPoint.Y) * zoom);

            }
        }

        private void openGLControl_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            System.Windows.Point MouseLoc = e.GetPosition(openGLControl); // Position relative to sharp GL control
            OpenGL gl = openGLControl.OpenGL;
            int w = (int)openGLControl.ActualWidth / 2, h = (int)openGLControl.ActualHeight / 2;

            
            
            if (e.Delta > 0)
            {
                zoom += 0.05;
                //if (zoom > 3) zoom = 3;
            }
            if (e.Delta < 0)
            {
                zoom -= 0.05;
                if (zoom < 0) zoom = 0.05;
            }
            lbCenter.Content = zoom.ToString();
            gl.Viewport(-w, w, -h, h);
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadIdentity();

            gl.Ortho2D(-w * zoom + center.X, w * zoom + center.X,
                -h * zoom + center.Y, h * zoom + center.Y);
        }

        private void openGLControl_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            System.Windows.Point Mouse = e.GetPosition(openGLControl);
            int w = (int)openGLControl.ActualWidth / 2, h = (int)openGLControl.ActualHeight / 2;
            switch (status % 10)
            {
                case 1:
                    Image nImg = new Image();
                    nImg.imgNum = status / 100;
                    nImg.depth = (double)(status%100) / 100;
                    nImg.x = (int)((mousePoint.X - w) * zoom + center.X);
                    nImg.y = (int)((-mousePoint.Y + h) * zoom + center.Y);
                    nImg.height = data[nImg.imgNum].Height;
                    nImg.width = data[nImg.imgNum].Width;

                    if ((status % 100) / 10 == 0)
                        BGList.Add(nImg);
                    if ((status % 100) / 10 == 1)
                        FGList.Add(nImg);
                    if ((status % 100) / 10 == 2)
                        RearList.Add(nImg);

                    break;
            }
        }
        

        private void openGLControl_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {
            rightButtonPoint = e.GetPosition(openGLControl); // Position relative to sharp GL control
            lbZoom.Content = rightButtonPoint.X + "," + rightButtonPoint.Y;
        }

        private void openGLControl_MouseRightButtonUp(object sender, MouseButtonEventArgs e)
        {
            center.X -= (mousePoint.X - rightButtonPoint.X)*zoom;
            center.Y += (mousePoint.Y - rightButtonPoint.Y)*zoom;

            lbZoom.Content = rightButtonPoint.X + "," + rightButtonPoint.Y;
            lbCenter.Content = center.X + "," + center.Y;
            rightButtonPoint.X = rightButtonPoint.Y = 0;

        }

        #endregion


        private void commandMouse()
        {
            status = 0;
        }
        


    }
}
