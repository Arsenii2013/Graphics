#ifndef SHADERWRAPPER_H
#define SHADERWRAPPER_H

#include <QtGui/QOpenGLShaderProgram>
#include <iostream>

class ShaderWrapper
{
public:
    QOpenGLShaderProgram *m_program;
public:
    ShaderWrapper() = default;
    ShaderWrapper(const std::string& vert_name, const std::string& frag_name, QObject *parent = nullptr){
        m_program = new QOpenGLShaderProgram(parent);
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(vert_name));
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(frag_name));
        if(!m_program->link()){
            throw std::runtime_error("Cannot link");
        }

        std::cout << m_program->log().toStdString() << std::endl;
    }

    GLuint getLocation(const std::string& name){
        GLuint uniform = m_program->uniformLocation(QString::fromStdString(name));
        GLuint attr = m_program->attributeLocation(QString::fromStdString(name));
        if(attr == -1 && uniform == -1){
            std::cout << m_program->log().toStdString() << std::endl;
            throw std::runtime_error(name + ": Not found in shader");
        }else if(attr != -1 && uniform != -1){
            std::cout << m_program->log().toStdString() << std::endl;
            throw std::runtime_error(name + ": It has both in shader");
        }

        return (attr != -1) ? attr : uniform;
    }

    template<typename T>
    void set(const std::string& name, T t){
        GLuint uniform = m_program->uniformLocation(QString::fromStdString(name));
        GLuint attr = m_program->attributeLocation(QString::fromStdString(name));
        if(attr == -1 && uniform == -1){
            std::cout << m_program->log().toStdString() << std::endl;
            throw std::runtime_error(name + ": Not found in shader");
        }else if(attr != -1 && uniform != -1){
            std::cout << m_program->log().toStdString() << std::endl;
            throw std::runtime_error(name + ": It has both in shader");
        }

        if(uniform != -1){
            m_program->setUniformValue(uniform, t);
        }else{
            std::cout << m_program->log().toStdString() << std::endl;
            throw std::runtime_error(name + ": U cant set attrib value");
        }
    }

    void setActive(){
        m_program->bind();
    }

    void deactivate(){
        m_program->release();
    }
};

#endif // SHADERWRAPPER_H
