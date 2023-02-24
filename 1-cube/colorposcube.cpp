#include "colorposcube.h"


#include <random>
#include <algorithm>

std::vector<QVector3D> ColorPosCube::genTrianglesFrontNormalizedInZero(int pointsPerSide){
    std::vector<QVector3D> res;
    pointsPerSide -= 1;
    GLfloat x = -0.5f;
    GLfloat y = -0.5f;
    GLfloat z = -0.5f;
    GLfloat dx = 1.f / pointsPerSide;
    GLfloat dy = 1.f / pointsPerSide;

    for(int i = 0; i < pointsPerSide; i++){
        for(int j = 0; j < pointsPerSide; j++){
            res.emplace_back(x + i*dx, y + j*dy, z); res.emplace_back(x + (i + 1)*dx, y + j*dy, z); res.emplace_back(x + i*dx, y + (j + 1)*dy, z);
            res.emplace_back(x + (i + 1)*dx, y + j*dy, z); res.emplace_back(x + (i + 1)*dx, y + (j + 1)*dy, z); res.emplace_back(x + i*dx, y + (j + 1)*dy, z);
        }
    }
    return res;
}

ColorPosCube::ColorPosCube(QVector3D center, GLfloat side, int pointsPerSide, GLenum primitive) : primitive(primitive){
    if(pointsPerSide < 2){
        throw std::invalid_argument("i cant gen side withs less then 2 points");
    }
    if(primitive == GL_TRIANGLES){
        auto frontSide = genTrianglesFrontNormalizedInZero(pointsPerSide);
        pointsCnt = frontSide.size() * 6;
        points = new GLfloat[pointsCnt * 3];
        colors = new GLfloat[pointsCnt * 3];

        std::vector<QVector3D> points3D;

        std::copy(frontSide.begin(), frontSide.end(), std::back_inserter(points3D));
        QMatrix4x4 rotate90aboutY;
        rotate90aboutY.rotate(90.f, 0, 1, 0);
        std::transform(frontSide.begin(), frontSide.end(), std::back_inserter(points3D), [&rotate90aboutY](const QVector3D& p){return rotate90aboutY*p;});
        QMatrix4x4 rotate180aboutY;
        rotate180aboutY.rotate(180.f, 0, 1, 0);
        std::transform(frontSide.begin(), frontSide.end(), std::back_inserter(points3D), [&rotate180aboutY](const QVector3D& p){return rotate180aboutY*p;});
        QMatrix4x4 rotate270aboutY;
        rotate270aboutY.rotate(270.f, 0, 1, 0);
        std::transform(frontSide.begin(), frontSide.end(), std::back_inserter(points3D), [&rotate270aboutY](const QVector3D& p){return rotate270aboutY*p;});
        QMatrix4x4 rotate90aboutX;
        rotate90aboutX.rotate(90.f, 1, 0, 0);
        std::transform(frontSide.begin(), frontSide.end(), std::back_inserter(points3D), [&rotate90aboutX](const QVector3D& p){return rotate90aboutX*p;});
        QMatrix4x4 rotate270aboutX;
        rotate270aboutX.rotate(270.f, 1, 0, 0);
        std::transform(frontSide.begin(), frontSide.end(), std::back_inserter(points3D), [&rotate270aboutX](const QVector3D& p){return rotate270aboutX*p;});

        for(int i = 0; i < pointsCnt; i++){
            points[i*3] = points3D[i].x();
            points[i*3 + 1] = points3D[i].y();
            points[i*3 + 2] = points3D[i].z();
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0., 1.);
        for(int i = 0; i < pointsCnt * 3; i++){
            colors[i] = dis(gen);
        }
    }else if(primitive == GL_TRIANGLE_STRIP){
        throw std::invalid_argument("unsupported primitive");
    }else{
        throw std::invalid_argument("unsupported primitive");
    }
}

void ColorPosCube::setColor(Side side, GLfloat r, GLfloat g, GLfloat b){
    if(primitive == GL_TRIANGLES){
        int start_pos;
        switch (side){
        case Side::FRONT:
            start_pos = 0;
            break;
        case Side::BACK:
            start_pos = 3 * pointsCnt / 6 * 3;
            break;
        case Side::RIGHT:
            start_pos = pointsCnt / 6 * 3;
            break;
        case Side::LEFT:
            start_pos = 2 * pointsCnt / 6 * 3;
            break;
        case Side::UP:
            start_pos = 4 * pointsCnt / 6 * 3;
            break;
        case Side::DOWN:
            start_pos = 5 * pointsCnt / 6 * 3;
            break;
        }
        for(int i = 0; i < pointsCnt / 6 ; i++){
            colors[i*3 + start_pos] = r;  colors[i*3 + 1 + start_pos] = g;  colors[i*3 + 2 + start_pos] = b;
        }
    }else if(primitive == GL_TRIANGLE_STRIP){
        throw std::invalid_argument("unsupported primitive");
    }
}

void ColorPosCube::setColor(Side side, QColor color){
    setColor(side, color.red(), color.green(), color.blue());
}

void ColorPosCube::setColor(Side side, QColor up_left, QColor up_right, QColor down_left, QColor down_right){
    throw std::invalid_argument("unsupported func!");
}

void ColorPosCube::setColor(GLfloat r, GLfloat g, GLfloat b){
    setColor(ColorPosCube::Side::FRONT, r, g, b);
    setColor(ColorPosCube::Side::BACK, r, g, b);
    setColor(ColorPosCube::Side::RIGHT, r, g, b);
    setColor(ColorPosCube::Side::LEFT, r, g, b);
    setColor(ColorPosCube::Side::DOWN, r, g, b);
    setColor(ColorPosCube::Side::UP, r, g, b);
}

int ColorPosCube::getPointsCnt(){
    return pointsCnt;
}

/*
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
 */

/*
        points[0] = center.x() - dev; points[1] = center.y() + dev; points[2] = center.z() + dev; // Front-top-left
        points[3] = center.x() + dev; points[4] = center.y() + dev; points[5] = center.z() + dev; // Front-top-right
        points[6] = center.x() - dev; points[7] = center.y() - dev; points[8] = center.z() + dev; // Front-bottom-left
        points[9] = center.x() + dev; points[10] = center.y() - dev; points[11] = center.z() + dev; // Front-bottom-right
        points[12] = center.x() + dev; points[13] = center.y() - dev; points[14] = center.z() - dev; // Back-bottom-right
        points[15] = center.x() + dev; points[16] = center.y() + dev; points[17] = center.z() + dev; // Front-top-right
        points[18] = center.x() + dev; points[19] = center.y() + dev; points[20] = center.z() - dev; // Back-top-right
        points[21] = center.x() - dev; points[22] = center.y() + dev; points[23] = center.z() + dev; // Front-top-left
        points[24] = center.x() - dev; points[25] = center.y() + dev; points[26] = center.z() - dev; // Back-top-left
        points[27] = center.x() - dev; points[28] = center.y() - dev; points[29] = center.z() + dev; // Front-bottom-left
        points[30] = center.x() - dev; points[31] = center.y() - dev; points[32] = center.z() - dev; // Back-bottom-left
        points[33] = center.x() + dev; points[34] = center.y() - dev; points[35] = center.z() - dev; // Back-bottom-right
        points[36] = center.x() - dev; points[37] = center.y() + dev; points[38] = center.z() - dev; // Back-top-left
        points[39] = center.x() + dev; points[40] = center.y() + dev; points[41] = center.z() - dev; // Back-top-right
        switch (side){
        case Side::FRONT:
            for(int i = 0; i < 4; i++){
                colors[i*3] = r;  colors[i*3 + 1] = g;  colors[i*3 + 2] = b;
            }
            colors[15] = r;  colors[16] = g;  colors[17] = b;
            colors[21] = r;  colors[22] = g;  colors[23] = b;
            colors[27] = r;  colors[28] = g;  colors[29] = b;
            break;
        case Side::BACK:
            colors[12] = r;  colors[13] = g;  colors[14] = b;
            colors[18] = r;  colors[19] = g;  colors[20] = b;
            colors[24] = r;  colors[25] = g;  colors[26] = b;
            for(int i = 0; i < 4; i++){
                colors[i*3 + 30] = r;  colors[i*3 + 1 + 30] = g;  colors[i*3 + 2 + 30] = b;
            }
            break;
        case Side::RIGHT:
            colors[3] = r;  colors[4] = g;  colors[4] = b;
            for(int i = 0; i < 4; i++){
                colors[i*3 + 9] = r;  colors[i*3 + 1 + 9] = g;  colors[i*3 + 2 + 9] = b;
            }
            colors[33] = r;  colors[34] = g;  colors[34] = b;
            colors[39] = r;  colors[40] = g;  colors[41] = b;
            break;
        case Side::LEFT:
            colors[0] = r;  colors[1] = g;  colors[2] = b;
            colors[6] = r;  colors[7] = g;  colors[8] = b;
            for(int i = 0; i < 4; i++){
                colors[i*3 + 21] = r;  colors[i*3 + 1 + 21] = g;  colors[i*3 + 2 + 21] = b;
            }
            colors[36] = r;  colors[37] = g;  colors[38] = b;
            break;
        case Side::UP:
            colors[0] = r;  colors[1] = g;  colors[2] = b;
            colors[3] = r;  colors[4] = g;  colors[4] = b;
            for(int i = 0; i < 4; i++){
                colors[i*3 + 15] = r;  colors[i*3 + 1 + 16] = g;  colors[i*3 + 2 + 17] = b;
            }
            colors[36] = r;  colors[37] = g;  colors[38] = b;
            colors[39] = r;  colors[40] = g;  colors[41] = b;
            break;
        case Side::DOWN:
            for(int i = 0; i < 3; i++){
                colors[i*3 + 6] = r;  colors[i*3 + 1 + 7] = g;  colors[i*3 + 2 + 8] = b;
            }
            for(int i = 0; i < 3; i++){
                colors[i*3 + 27] = r;  colors[i*3 + 1 + 28] = g;  colors[i*3 + 2 + 29] = b;
            }
            break;
        }
    }
 */
