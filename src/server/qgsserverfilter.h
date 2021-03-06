/***************************************************************************
                          qgsserverfilter.h
 Server I/O filters class for QGIS Server for use by plugins
                          -------------------
  begin                : 2014-09-10
  copyright            : (C) 2014 by Alessandro Pasotti
  email                : a dot pasotti at itopen dot it
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef QGSSERVERFILTER_H
#define QGSSERVERFILTER_H

#include <QMultiMap>
#include "qgis_server.h"
#include "qgis_sip.h"

SIP_IF_MODULE( HAVE_SERVER_PYTHON_PLUGINS )

class QgsServerInterface;

/**
 * \ingroup server
 * \class QgsServerFilter
 * \brief Class defining I/O filters for QGIS Server and
 * implemented in plugins.
 *
 * Filters can define any (or none) of the following hooks:
 *
 * - requestReady() - called when request is ready
 * - responseComplete() - called when the response is complete after core services have returned to main loop
 * - sendResponse() - called just before sending output to FGCI
 */
class SERVER_EXPORT QgsServerFilter
{

  public:

    /**
     * Constructor
     * QgsServerInterface passed to plugins constructors
     * and must be passed to QgsServerFilter instances.
     */
    QgsServerFilter( QgsServerInterface *serverInterface );

    virtual ~QgsServerFilter() = default;

    //! Returns the QgsServerInterface instance
    QgsServerInterface *serverInterface() { return mServerInterface; }

    /**
     * Method called when the QgsRequestHandler is ready and populated with
    * parameters, just before entering the main switch for core services.
    */
    virtual void requestReady();

    /**
     * Method called when the QgsRequestHandler processing has done and
     * the response is ready, just after the main switch for core services
     * and before final sending response to FCGI stdout.
     */
    virtual void responseComplete();

    /**
     * Method called when the QgsRequestHandler sends its data to FCGI stdout.
     * This normally occurs at the end of core services processing just after
     * the responseComplete() plugin hook. For streaming services (like WFS on
     * getFeature requests, sendResponse() might have been called several times
     * before the response is complete: in this particular case, sendResponse()
     * is called once for each feature before hitting responseComplete()
     */
    virtual void sendResponse();

  private:

    QgsServerInterface *mServerInterface = nullptr;

};

typedef QMultiMap<int, QgsServerFilter *> QgsServerFiltersMap;

#endif // QGSSERVERFILTER_H
