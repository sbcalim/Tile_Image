/*
 * =====================================================================================
 *
 *       Filename:  try.cpp
 *
 *    Description:  Tile an image, resize each pece and give output
 *
 *        Version:  1.0
 *        Created:  11/14/2017 09:47:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SITKI BURAK CALIM (), sburakcalim@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <opencv2/opencv.hpp>
#include <Magick++.h>
#include <iostream>

//File name array. Output file names will be taken from this array
const std::string name_array[] = { "1.jpg",  "2.jpg",  "3.jpg",  "4.jpg",  "5.jpg",  "6.jpg",  "7.jpg",  "8.jpg",  "9.jpg",  "10.jpg",  "11.jpg",  "12.jpg",  "13.jpg",  "14.jpg",  "15.jpg",  "16.jpg" };

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  help
 *  Description:  Explains usage
 * =====================================================================================
 */
    void
help ( std::string filename )
{
    std::cout << "Usage: " << std::endl;
    std::cout << filename << " filename" << std::endl;
}		/* -----  end of function help  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  resizeTile
 *  Description:  Resize the given matrix image according to given x and y values
 * =====================================================================================
 */
    cv::Mat
resizeTile ( cv::Mat img, int x, int y )
{
    cv::Mat retval;                 // Matrix to return declaration
    cv::Size size( x, y );          // Prepare size value to be used in resize( ) function
    resize( img, retval, size );    // Resize img variable according to size variable and write output to retval
    return retval;
}		/* -----  end of function resizeTile  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  divide
 *  Description:  Tile image and use resizeTile function to resize each piece.
 *                  Finally creates output for all pieces with names taken from name_array
 * =====================================================================================
 */
    void
divide ( cv::Mat image, int number_of_rows, int number_of_columns, int x, int y )
{
    int w = image.cols / number_of_columns; // w : Tiled piece width
    int h = image.rows / number_of_rows;    // h : Tiled piece height

    cv::Rect temp;      // temp = Frame to be used for specifying which part if image will be taken
    int index = 0;      // for name_array indexing

    //Go for all wanted pieces. Each column piece for each row piece
    for( int i = 0; i < number_of_rows; i++ )
    {
        for( int j = 0; j < number_of_columns; j++ )
        {
            temp.x = i * w;     //Upper left corner x value
            temp.y = j * h;     //Upper left corner y value

            temp.width = w;     //Frame width
            temp.height = h;    //Frame height

            //Take inside of temp rectangle, give name from name_array and create output
            imwrite( name_array[index++], resizeTile( image( temp ), x, y ) );
        }
    }

}		/* -----  end of function divide  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  Main function
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{
    if( argc != 2 )
    {
        help( argv[0] );
        exit( 0 );
    }
        
    Magick::InitializeMagick( *argv );  //Magick constructor


    /* ****************************************************************** */
    /****** Change this line to read different image in any format ********/
    Magick::Image image( argv[1] ); //Read image


    int w = image.columns( );               // w : Width of the given image. Will be used to create OpenCV matrix
    int h = image.rows( );                  // h : Height of the given image. Will be used to create OpenCV matrix
    cv::Mat opencv_image( h, w, CV_8UC3 );  // Create 8bits unsigned char OpenCV matrix to put image in.
    /*
     * CV_8UC3 alternatives:
     * http://ninghang.blogspot.com.tr/2012/11/list-of-mat-type-in-opencv.html
     */

    //Write Magick image into OpenCV matrix
    image.write( 0, 0, w, h, "BGR", Magick::CharPixel, opencv_image.data );

    std::string row_count, column_count, x, y;
    std::cout << "Enter the row count: "; std::cin >> row_count;        // row_count : How many pieces vertically
    std::cout << "Enter the column count: "; std::cin >> column_count;  // column_count : How many pieces horizontally
    std::cout << "Enter x size: "; std::cin >> x;                       // Resolution x value for one piece
    std::cout << "Enter y size: "; std::cin >> y;                       // Resolution y value for one piece
    
    //Apply tiling process
    divide( opencv_image, atoi( row_count.c_str( ) ), atoi( column_count.c_str( ) ), atoi( x.c_str( ) ), atoi( y.c_str( ) ) );

    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
