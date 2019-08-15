#include "NorthArrowController.h"

#include "MapGraphicsView.h"

NorthArrowController::NorthArrowController(QObject* parent):
  QObject(parent)
{
}

NorthArrowController::~NorthArrowController()
{
}

void NorthArrowController::resetRotation()
{
  if (m_mapView)
  {
    m_mapView->setViewpointRotation(0);
  }
}

Esri::ArcGISRuntime::MapGraphicsView* NorthArrowController::mapView() const
{
  return m_mapView;
}

void NorthArrowController::setMapView(Esri::ArcGISRuntime::MapGraphicsView* mapView)
{
  if (mapView == m_mapView)
    return;

  m_mapView = mapView;
  emit mapViewChanged();

  if (!m_mapView)
    return;

  connect(m_mapView, &Esri::ArcGISRuntime::MapGraphicsView::mapRotationChanged, this, &NorthArrowController::rotationChanged);
}

int NorthArrowController::rotation() const
{
  return m_mapView ? m_mapView->mapRotation() : 0;
}