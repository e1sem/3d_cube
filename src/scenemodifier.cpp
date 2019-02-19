#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPhongMaterial>

#include <QUrl>

#include <memory>

#include "scenemodifier.hpp"
#include "parameters.hpp"
#include "modelloader.hpp"

/******************************************************************************/

SceneModifier::SceneModifier(
         Qt3DCore::QEntity* rootEntity
    )
{
    // CuboidMesh Transform
    m_transformData = new Qt3DCore::QTransform();

    m_transformData->setScale( ProjOpt::cuboidScale );
    m_transformData->setTranslation( QVector3D( 5.0f, 5.0f, 5.0f ) );
    m_transformData->setScale( 0.25f );

    // Cuboid material init
    Qt3DExtras::QPhongMaterial* modelMaterial = new Qt3DExtras::QPhongMaterial();

    modelMaterial->setDiffuse( ProjOpt::cuboidColor );

    m_modelEntity = new Qt3DCore::QEntity( rootEntity );
    m_modelEntity->addComponent( modelMaterial );
    m_modelEntity->addComponent( m_transformData );

    // Cuboid shape data
    Qt3DExtras::QCuboidMesh* cuboid = new Qt3DExtras::QCuboidMesh();

    m_modelEntity->addComponent( cuboid );
}

/******************************************************************************/

void
SceneModifier::setModelLoader( ModelLoader* _modelLoader )
{
    m_pModelLoader = _modelLoader;
}

/******************************************************************************/

void
SceneModifier::enableCuboid( bool enabled ) noexcept
{
    m_modelEntity->setEnabled( enabled );
}

/******************************************************************************/

void
SceneModifier::setCuboidRotationX( float _angle ) noexcept
{
    m_transformData->setRotationX( _angle );
}

/******************************************************************************/

void
SceneModifier::setCuboidRotationY( float _angle ) noexcept
{
    m_transformData->setRotationZ( _angle );
}

/******************************************************************************/

float
SceneModifier::getCuboidRotationX() noexcept
{
    return m_transformData->rotationX();
}

/******************************************************************************/

float
SceneModifier::getCuboidRotationY() noexcept
{
    return m_transformData->rotationZ();
}

/******************************************************************************/

void
SceneModifier::onModelPathChanged()
{
    m_objModel = new Qt3DRender::QMesh();
    m_objModel->setSource(
            QUrl::fromLocalFile(
                     m_pModelLoader->getPathToModel()
            )
    );

    m_modelEntity->addComponent( m_objModel );
}

/******************************************************************************/
