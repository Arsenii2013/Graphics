#ifndef SELECTCOLOR_H
#define SELECTCOLOR_H

#include <QPushButton>
#include <QColor>

class SelectColorButton : public QPushButton
{
    Q_OBJECT
public:
    SelectColorButton( QWidget* parent );

    void setColor( const QColor& color );
    const QColor& getColor() const;

public slots:
    void updateColor();
    void changeColor();

private:
    QColor color;

signals:
    void colorChanged(const QColor& color);
};

#endif // SELECTCOLOR_H
