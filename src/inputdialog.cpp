#include <QtGui>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QCommonStyle>

#include <QtCore/QDebug>

#include "inputdialog.hpp"
#include "parameters.hpp"
#include "serialport.hpp"

/******************************************************************************/

InputDialog::InputDialog( QWidget* _pWidget )
     :  QDialog(
                _pWidget
            ,       Qt::WindowTitleHint
                |   Qt::WindowSystemMenuHint
                |   Qt::WindowCloseButtonHint
        )
{
    m_pSerialPort = nullptr;

    initializeWidget();
    addElements();
    fillComboBoxes();
}

/******************************************************************************/

void
InputDialog::setSerialPort( VirtualPort* _pComPort ) noexcept
{
    m_pSerialPort = _pComPort;
}

/******************************************************************************/

QString
InputDialog::getComPort() const noexcept
{
    return m_pTxtComPort->currentText();
}

/******************************************************************************/

QString
InputDialog::getBaudRate() const noexcept
{
    return m_pTxtBaudRate->currentText();
}

/******************************************************************************/

void
InputDialog::initializeWidget() noexcept
{
    setWindowIcon( style()->standardIcon( QStyle::SP_DialogYesButton ) );
    setWindowModality( Qt::WindowModal );
    setWindowTitle( "Port config" );
    setFixedSize( 200, 120 );
}

/******************************************************************************/

void
InputDialog::addElements() noexcept
{
    m_pTxtComPort = new QComboBox( this );
    m_pTxtBaudRate  = new QComboBox( this );

    QLabel* pLblComPort = new QLabel( "&COM Port:", this );
    QLabel* pLblBaudRate = new QLabel( "&Baud rate:", this );

    pLblComPort->setBuddy( m_pTxtComPort );
    pLblBaudRate->setBuddy( m_pTxtBaudRate );

    QPushButton* cmdOk = new QPushButton( "&Ok", this );
    QPushButton* cmdCancel = new QPushButton( "&Cancel", this );

    QGridLayout* pTopLayout = new QGridLayout;
    pTopLayout->addWidget( pLblComPort, 0, 0 );
    pTopLayout->addWidget( pLblBaudRate, 1, 0 );
    pTopLayout->addWidget( m_pTxtComPort, 0, 1 );
    pTopLayout->addWidget( m_pTxtBaudRate, 1, 1 );
    pTopLayout->addWidget( cmdOk, 2,0 );
    pTopLayout->addWidget( cmdCancel, 2, 1 );

    setLayout( pTopLayout );

    connect(
            cmdOk
        ,   &QPushButton::clicked
        ,   this
        ,   &InputDialog::dialogClose
    );
    connect(
            cmdCancel
        ,   &QPushButton::clicked
        ,   this
        ,   &InputDialog::reject
    );
}

/******************************************************************************/

void
InputDialog::fillComboBoxes() noexcept
{
    // Avaliable COM Ports
    auto serialPorts = QSerialPortInfo::availablePorts();

    for( auto && port : serialPorts)
        m_pTxtComPort->addItem( port.portName() );

    // Standard baud rates
    QStringList baudList = {
            "1200"
        ,   "2400"
        ,   "4800"
        ,   "9600"
        ,   "19200"
        ,   "38400"
        ,   "57600"
        ,   "115200"
    };

    m_pTxtBaudRate->addItems( baudList );
    m_pTxtBaudRate->setCurrentIndex( baudList.size() - 1 );
}

/******************************************************************************/

void
InputDialog::dialogClose()
{
    if( m_pSerialPort != nullptr )
        m_pSerialPort->openComPort(
                getComPort()
            ,   getBaudRate()
        );
    accept();
}

/******************************************************************************/
