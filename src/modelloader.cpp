#include "modelloader.hpp"
#include "scenemodifier.hpp"

#include <QShortcut>

/******************************************************************************/

ModelLoader::ModelLoader( QWidget* _parent )
    :    QWidget( _parent )
{
    m_keyCtlD = new QShortcut ( this );
    m_keyCtlD->setKey( Qt::CTRL + Qt::Key_D );
}

/******************************************************************************/

ModelLoader::~ModelLoader() = default;

/******************************************************************************/

QString
ModelLoader::getPathToModel() const
{
    return m_pathToModel;
}

/******************************************************************************/

void
ModelLoader::connectSignals()
{
    connect(
            m_keyCtlD
        ,   &QShortcut::activated
        ,   this
        ,   &ModelLoader::hotkeyClicked
    );

    connect(
            this
        ,   &ModelLoader::modelPathChanged
        ,   m_pSceneModifier
        ,   &SceneModifier::onModelPathChanged
    );
}

/******************************************************************************/

void
ModelLoader::setSceneModifier( SceneModifier* _sceneModifier )
{
    m_pSceneModifier = _sceneModifier;
    connectSignals();
}

/******************************************************************************/

void
ModelLoader::hotkeyClicked()
{
    QFileDialog filePicker {this};
    filePicker.setNameFilter( tr("3D models files( *.obj )") );

    m_pathToModel = filePicker.getOpenFileName();

    if( !m_pathToModel.isEmpty() )
        emit modelPathChanged();
}


/******************************************************************************/

