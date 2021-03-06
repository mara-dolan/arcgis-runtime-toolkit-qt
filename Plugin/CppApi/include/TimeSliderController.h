/*******************************************************************************
 *  Copyright 2012-2018 Esri
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ******************************************************************************/

#ifndef TIMESLIDERCONTROLLER_H
#define TIMESLIDERCONTROLLER_H

// toolkit headers
#include "AbstractTool.h"

// C++ API headers
#include "TimeExtent.h"

// Qt headers
#include <QVariantList>

namespace Esri
{
namespace ArcGISRuntime
{

class GeoView;
class LayerListModel;
class MapQuickView;
class SceneQuickView;

namespace Toolkit
{

class TOOLKIT_EXPORT TimeSliderController : public AbstractTool
{
  Q_OBJECT

  Q_PROPERTY(int numberOfSteps READ numberOfSteps NOTIFY numberOfStepsChanged)
  Q_PROPERTY(QDateTime fullExtentStart READ fullExtentStart NOTIFY fullTimeExtentChanged)
  Q_PROPERTY(QDateTime fullExtentEnd READ fullExtentEnd NOTIFY fullTimeExtentChanged)
  Q_PROPERTY(QDateTime currentExtentStart READ currentExtentStart NOTIFY currentTimeExtentChanged)
  Q_PROPERTY(QDateTime currentExtentEnd READ currentExtentEnd NOTIFY currentTimeExtentChanged)
  Q_PROPERTY(int startStep READ startStep NOTIFY startStepChanged)
  Q_PROPERTY(int endStep READ endStep NOTIFY endStepChanged)
  Q_PROPERTY(QVariantList stepTimes READ stepTimes NOTIFY stepTimesChanged)
  Q_PROPERTY(QObject* geoView READ geoView WRITE setGeoView NOTIFY geoViewChanged)

signals:
  void numberOfStepsChanged();
  void fullTimeExtentChanged();
  void currentTimeExtentChanged();
  void startStepChanged();
  void endStepChanged();
  void stepTimesChanged();
  void geoViewChanged();

public:
  TimeSliderController(QObject* parent = nullptr);
  ~TimeSliderController() override;

  QString toolName() const override;

  QObject* geoView() const;
  void setGeoView(QObject* geoView);

  int numberOfSteps() const;

  Esri::ArcGISRuntime::TimeExtent fullTimeExtent() const;
  QDateTime fullExtentStart() const;
  QDateTime fullExtentEnd() const;

  Esri::ArcGISRuntime::TimeExtent currentTimeExtent() const;
  QDateTime currentExtentStart() const;
  QDateTime currentExtentEnd() const;

  int startStep() const;
  int endStep() const;

  QVariantList stepTimes() const;

  Q_INVOKABLE void setStartInterval(int intervalIndex);
  Q_INVOKABLE void setEndInterval(int intervalIndex);
  Q_INVOKABLE void setStartAndEndIntervals(int startIndex, int endIndex);

private slots:
  void onOperationalLayersChanged();
  void onMapChanged();
  void onSceneChanged();

private:
  void initializeTimeProperties();

  void setNumberOfSteps(int numberOfSteps);
  void setStepTimes();
  void setFullTimeExtent(const Esri::ArcGISRuntime::TimeExtent& fullTimeExtent);
  void setStartStep(int startStep);
  void setEndStep(int endStep);
  void calculateStepPositions();

  Esri::ArcGISRuntime::MapQuickView* m_mapView = nullptr;
  Esri::ArcGISRuntime::SceneQuickView* m_sceneView = nullptr;
  Esri::ArcGISRuntime::LayerListModel* m_operationalLayers = nullptr;
  Esri::ArcGISRuntime::TimeExtent m_fullTimeExtent;
  QVariantList m_stepTimes;

  int m_numberOfSteps = -1;
  double m_intervalMS = -1;
  int m_startStep = -1;
  int m_endStep = -1;
};

} // Toolkit
} // ArcGISRuntime
} // Esri

#endif // TIMESLIDERCONTROLLER_H
