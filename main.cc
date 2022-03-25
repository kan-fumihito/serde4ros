#include<iostream>
#include<string>
#include<cstdint>
#include"std_msgs/Header.h"
#include"std_msgs/Image.h"
#include"std_msgs/Time.h"

int main(void){

    Image img;
    Header header;
    Time time;
    
    time.time=1234;

    header.seq=1;
    header.frame_id=std::string("b1018262");
    header.stamp.time=time.time;

    img.height=42;
    img.width=23;
    img.encoding=std::string("jpeg");
    img.is_bigendian=0;
    img.step=100;
    
    img.data.resize(img.height * img.width);
    for(int i=0;i<img.data.size();i++){
      img.data[i] = i % 255;
    }

    img.header.seq=header.seq;
    img.header.frame_id=header.frame_id;
    img.header.stamp.time=header.stamp.time;

    std::string first("image1.dat");
    img.serialize(first);

    Image dimg;
    dimg.deserialize(first);

    std::string second("image2.dat");
    dimg.serialize(second);

    return 0;
}
