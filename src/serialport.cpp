#include <QtCore/QDebug>

#include "scenemodifier.hpp"
#include "parameters.hpp"
#include "serialport.hpp"

/******************************************************************************/

VirtualPort::VirtualPort( QObject* _parent )
    :   QObject{ _parent }
    ,   m_hComPort { nullptr }
    ,   m_pModifier { nullptr }
{
}

/******************************************************************************/

VirtualPort::~VirtualPort()
{
    if( m_hComPort == nullptr )
        return;

    if( m_hComPort->isOpen() )
        m_hComPort->close();

    qDebug() << "-----------------------------------";
    qDebug() << "          COMPORT CLOSED           ";
    qDebug() << "-----------------------------------";
}

/******************************************************************************/

void
VirtualPort::setModifier( SceneModifier* _modifier ) noexcept
{
    m_pModifier = _modifier;
}

/******************************************************************************/

void
VirtualPort::openComPort( QString _name, QString _speed )
{
    if( m_hComPort != nullptr )
        return;

    m_hComPort = new QSerialPort{ this };

    connectReadEvent();

    m_hComPort->setPortName( _name );
    m_hComPort->setBaudRate( _speed.toInt() );
    m_hComPort->setDataBits( QSerialPort::Data8 );
    m_hComPort->setParity( QSerialPort::NoParity );
    m_hComPort->setStopBits( QSerialPort::OneStop );
    m_hComPort->setFlowControl( QSerialPort::NoFlowControl );

    if ( m_hComPort->open( QIODevice::ReadOnly ) )
    {
        qDebug() << "-----------------------------------";
        qDebug() << "          COMPORT OPENED           ";
        qDebug() << "-----------------------------------";
    }
    else
        qDebug() << "Error"
                 << m_hComPort->error()
                 << " : "
                 << m_hComPort->errorString();
}

/******************************************************************************/

void
VirtualPort::readData()
{
    QByteArray axisXY = m_hComPort->readAll();

    if( axisXY.size() != ProjOpt::packageSize )
    {
        qDebug() << "Incompatible data format!"
                 << " Expected: "
                 << ProjOpt::packageSize
                 << " Provided: "
                 << axisXY.size();
        return;
    }

    int coordX = static_cast<int>( axisXY.data()[0] );
    int coordY = static_cast<int>( axisXY.data()[1] );

    if( isUpdateNeeded( coordX, coordY ) )
    {
        m_pModifier->setCuboidRotationX( coordX );
        m_pModifier->setCuboidRotationY( coordY );

        // continuous debug output
        qDebug() << "X: " << coordX;
        qDebug() << "Y: " << coordY;
        qDebug() << '\n';
    }
}

/******************************************************************************/

void
VirtualPort::connectReadEvent() noexcept
{
    connect(
            m_hComPort
        ,   &QSerialPort::readyRead
        ,   this
        ,   &VirtualPort::readData
    );
}

/******************************************************************************/

bool
VirtualPort::isUpdateNeeded( int _angleX, int _angleY ) noexcept
{
    if( m_pModifier == nullptr )
        return false;

    if(
            abs( _angleX - m_pModifier->getCuboidRotationX() ) > ProjOpt::coordEps
        ||  abs( _angleY - m_pModifier->getCuboidRotationY() ) > ProjOpt::coordEps
    )
        return true;

    return false;
}

/******************************************************************************/

