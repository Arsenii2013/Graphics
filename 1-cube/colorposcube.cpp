#include "colorposcube.h"


#include <random>

ColorPosCube::ColorPosCube(QVector3D center, GLfloat side, GLenum primitive) : primitive(primitive){
    GLfloat dev = side / 2;
    if(primitive == GL_TRIANGLES){
        int arrsize = 36 * 3;
        points = new GLfloat[arrsize];
        colors = new GLfloat[arrsize];
        //FRONT
        //FIRST TRIANGLE
        points[0] = center.x() - dev; points[1] = center.y() - dev; points[2] = center.z() - dev; // DOWN LEFT
        points[3] = center.x() + dev; points[4] = center.y() + dev; points[5] = center.z() - dev; // UP RIGHT
        points[6] = center.x() - dev; points[7] = center.y() + dev; points[8] = center.z() - dev; // UP LEFT
        //SECOND TRIANGLE
        points[9] = center.x() - dev; points[10] = center.y() - dev; points[11] = center.z() - dev; // DOWN LEFT
        points[12] = center.x() + dev; points[13] = center.y() - dev; points[14] = center.z() - dev; // DOWN RIGHT
        points[15] = center.x() + dev; points[16] = center.y() + dev; points[17] = center.z() - dev; // UP RIGHT
        //BACK
        //FIRST TRIANGLE
        points[18] = center.x() - dev; points[19] = center.y() - dev; points[20] = center.z() + dev; // DOWN LEFT
        points[21] = center.x() - dev; points[22] = center.y() + dev; points[23] = center.z() + dev; // UP LEFT
        points[24] = center.x() + dev; points[25] = center.y() + dev; points[26] = center.z() + dev; // UP RIGHT
        //SECOND TRIANGLE
        points[27] = center.x() - dev; points[28] = center.y() - dev; points[29] = center.z() + dev; // DOWN LEFT
        points[30] = center.x() + dev; points[31] = center.y() + dev; points[32] = center.z() + dev; // UP RIGHT
        points[33] = center.x() + dev; points[34] = center.y() - dev; points[35] = center.z() + dev; // DOWN RIGHT
        //RIGHT
        //FIRST TRIANGLE
        points[36] = center.x() + dev; points[37] = center.y() - dev; points[38] = center.z() - dev; // DOWN LEFT
        points[39] = center.x() + dev; points[40] = center.y() + dev; points[41] = center.z() + dev; // UP RIGHT
        points[42] = center.x() + dev; points[43] = center.y() + dev; points[44] = center.z() - dev; // UP LEFT
        //SECOND TRIANGLE
        points[45] = center.x() + dev; points[46] = center.y() - dev; points[47] = center.z() - dev; // DOWN LEFT
        points[48] = center.x() + dev; points[49] = center.y() - dev; points[50] = center.z() + dev; // DOWN RIGHT
        points[51] = center.x() + dev; points[52] = center.y() + dev; points[53] = center.z() + dev; // UP RIGHT
        //LEFT
        //FIRST TRIANGLE
        points[54] = center.x() - dev; points[55] = center.y() - dev; points[56] = center.z() - dev; // DOWN LEFT
        points[57] = center.x() - dev; points[58] = center.y() + dev; points[59] = center.z() - dev; // UP LEFT
        points[60] = center.x() - dev; points[61] = center.y() + dev; points[62] = center.z() + dev; // UP RIGHT
        //SECOND TRIANGLE
        points[63] = center.x() - dev; points[64] = center.y() - dev; points[65] = center.z() - dev; // DOWN LEFT
        points[66] = center.x() - dev; points[67] = center.y() + dev; points[68] = center.z() + dev; // UP RIGHT
        points[69] = center.x() - dev; points[70] = center.y() - dev; points[71] = center.z() + dev; // DOWN RIGHT
        //UP
        //FIRST TRIANGLE
        points[72] = center.x() - dev; points[73] = center.y() + dev; points[74] = center.z() - dev; // DOWN LEFT
        points[75] = center.x() + dev; points[76] = center.y() + dev; points[77] = center.z() + dev; // UP RIGHT
        points[78] = center.x() - dev; points[79] = center.y() + dev; points[80] = center.z() + dev; // UP LEFT
        //SECOND TRIANGLE
        points[81] = center.x() - dev; points[82] = center.y() + dev; points[83] = center.z() - dev; // DOWN LEFT
        points[84] = center.x() + dev; points[85] = center.y() + dev; points[86] = center.z() - dev; // DOWN RIGHT
        points[87] = center.x() + dev; points[88] = center.y() + dev; points[89] = center.z() + dev; // UP RIGHT
        //DOWN
        //FIRST TRIANGLE
        points[90] = center.x() - dev; points[91] = center.y() - dev; points[92] = center.z() - dev; // DOWN LEFT
        points[93] = center.x() - dev; points[94] = center.y() - dev; points[95] = center.z() + dev; // UP LEFT
        points[96] = center.x() + dev; points[97] = center.y() - dev; points[98] = center.z() + dev; // UP RIGHT
        //SECOND TRIANGLE
        points[99] = center.x() - dev; points[100] = center.y() - dev; points[101] = center.z() - dev; // DOWN LEFT
        points[102] = center.x() + dev; points[103] = center.y() - dev; points[104] = center.z() + dev; // UP RIGHT
        points[105] = center.x() + dev; points[106] = center.y() - dev; points[107] = center.z() - dev; // DOWN RIGHT

        //COLORS
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0., 1.);
        for(int i = 0; i < arrsize; i++){
            colors[i] = dis(gen);
        }
    }else if(primitive == GL_TRIANGLE_STRIP){
        int arrsize = 14 * 3;
        points = new GLfloat[arrsize];
        colors = new GLfloat[arrsize];

        points[0] = center.x() - dev; points[1] = center.y() + dev; points[2] = center.z() + dev; // UP LEFT FRONT
        points[3] = center.x() + dev; points[4] = center.y() + dev; points[5] = center.z() + dev; // DOWN LEFT FRONT
        points[6] = center.x() - dev; points[7] = center.y() - dev; points[8] = center.z() + dev; // UP RIGHT FRONT
        points[9] = center.x() + dev; points[10] = center.y() - dev; points[11] = center.z() + dev; // DOWN RIGHT FRONT
        points[12] = center.x() + dev; points[13] = center.y() - dev; points[14] = center.z() - dev; // UP RIGHT BACK
        points[15] = center.x() + dev; points[16] = center.y() + dev; points[17] = center.z() + dev; // DOWN RIGHT BACK
        points[18] = center.x() + dev; points[19] = center.y() + dev; points[20] = center.z() - dev; // DOWN RIGHT BACK
        points[21] = center.x() - dev; points[22] = center.y() + dev; points[23] = center.z() + dev; // DOWN RIGHT BACK
        points[24] = center.x() - dev; points[25] = center.y() + dev; points[26] = center.z() - dev; // DOWN RIGHT BACK
        points[27] = center.x() - dev; points[28] = center.y() - dev; points[29] = center.z() + dev; // DOWN RIGHT BACK
        points[30] = center.x() - dev; points[31] = center.y() - dev; points[32] = center.z() - dev; // DOWN RIGHT BACK
        points[33] = center.x() + dev; points[34] = center.y() - dev; points[35] = center.z() - dev; // DOWN RIGHT BACK
        points[36] = center.x() - dev; points[37] = center.y() + dev; points[38] = center.z() - dev; // DOWN RIGHT BACK
        points[39] = center.x() + dev; points[40] = center.y() + dev; points[41] = center.z() - dev; // DOWN RIGHT BACK

        //COLORS
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0., 1.);
        for(int i = 0; i < arrsize; i++){
            colors[i] = dis(gen);
        }
    }else{
        throw std::invalid_argument("unsupported primitive");
    }
}

int ColorPosCube::getPointsCnt(){
    if(primitive == GL_TRIANGLES){
        return 36;
    }else if(primitive == GL_TRIANGLE_STRIP){
        return 14;
    }
}
