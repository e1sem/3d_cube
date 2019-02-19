#ifndef CUBE3D_INPUTDIALOG_HPP_
#define CUBE3D_INPUTDIALOG_HPP_

/******************************************************************************/

#include <QDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>

/******************************************************************************/

class VirtualPort;

/******************************************************************************/

class InputDialog
    :   public QDialog
{

/******************************************************************************/

    Q_OBJECT

/******************************************************************************/

public:

/******************************************************************************/

    InputDialog( QWidget* _pWidget = nullptr );

    ~InputDialog() = default;

/******************************************************************************/

    void setSerialPort( VirtualPort* _pComPort ) noexcept;

    QString getComPort() const noexcept;

    QString getBaudRate() const noexcept;

/******************************************************************************/

private:

/******************************************************************************/

    void initializeWidget() noexcept;

    void addElements() noexcept;

    void fillComboBoxes() noexcept;

/******************************************************************************/

private slots:

/******************************************************************************/

    void dialogClose();

/******************************************************************************/

private:

/******************************************************************************/

    VirtualPort* m_pSerialPort;

    QComboBox* m_pTxtComPort;

    QComboBox* m_pTxtBaudRate;

/******************************************************************************/

}; // class InputDialog

/******************************************************************************/

#endif // CUBE3D_INPUTDIALOG_HPP_
