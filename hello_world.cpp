#include <iostream>
#include "image.h"

int main() {
    std::cout << "Hello world!" << std::endl;

    image my_image(512,512 );

    my_image.fill_ellipse(1,256,256,150,200);
    my_image.fill_ellipse(0.3,256,260,140,180,false);
    my_image.fill_ellipse(0.2,256,180,50,60,true);
    my_image.fill_ellipse(-0.2,200,220,30,80,true);
    my_image.fill_ellipse(-0.2,310,230,20,50,true);
    my_image.fill_ellipse(0.2,230,350,10,10,true);
    my_image.fill_ellipse(0.2,260,350,10,20,true);

    my_image.save("img");
    system("python ../display.py");
}