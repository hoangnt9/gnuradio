/* -*- c++ -*- */
/*
 * Copyright 2012,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_QTGUI_TIME_RASTER_SINK_B_H
#define INCLUDED_QTGUI_TIME_RASTER_SINK_B_H

#include <Python.h>
#include <qtgui/api.h>
#include <gr_sync_block.h>
#include <qapplication.h>
#include <qwt_symbol.h>

namespace gr {
  namespace qtgui {

    /*!
     * \brief A graphical sink to display multiple signals on a
     * time_raster plot.
     * \ingroup qtgui_blk
     *
     * This is a QT-based graphical sink that takes in byte
     * streams and plots a time_raster (spectrogram) plot.
     *
     * Input stream: This expects a bit stream (0, 1 in the LSB of a
     * byte). It will display packed bytes but the display will have
     * to be autoscaled.
     */
    class QTGUI_API time_raster_sink_b : virtual public gr_sync_block
    {
    public:
      // gr::qtgui::time_raster_sink_b::sptr
      typedef boost::shared_ptr<time_raster_sink_b> sptr;

      /*!
       * \brief Build a bit time raster sink.
       *
       * \param samp_rate sample rate of signal
       * \param cols number of cols to plot
       * \param rows number of rows to plot
       * \param mult vector of floats as a scaling multiplier for each input stream
       * \param offset vector of floats as an offset for each input stream
       * \param name title for the plot
       * \param nconnections number of streams connected
       * \param parent a QWidget parent object, if any
       */
      static sptr make(double samp_rate,
		       double rows, double cols,
		       const std::vector<float> &mult,
		       const std::vector<float> &offset,
		       const std::string &name,
		       int nconnections=1,
		       QWidget *parent=NULL);

      virtual void exec_() = 0;
      virtual PyObject* pyqwidget() = 0;

      virtual void set_update_time(double t) = 0;
      virtual void set_title(const std::string &title) = 0;
      virtual void set_line_label(const std::string &lable) = 0;
      virtual void set_line_color(const std::string &color) = 0;
      virtual void set_line_width(int width) = 0;
      virtual void set_line_style(Qt::PenStyle style) = 0;
      virtual void set_line_marker(QwtSymbol::Style marker) = 0;

      virtual void set_size(int width, int height) = 0;

      virtual void set_num_rows(double rows) = 0;
      virtual void set_num_cols(double cols) = 0;

      virtual double num_rows() = 0;
      virtual double num_cols() = 0;

      virtual void set_multiplier(const std::vector<float> &mult) = 0;
      virtual void set_offset(const std::vector<float> &offset) = 0;

      virtual void set_intensity_range(float min, float max) = 0;

      virtual void reset() = 0;

      QApplication *d_qApplication;
    };

  } /* namespace qtgui */
} /* namespace gr */

#endif /* INCLUDED_QTGUI_TIME_RASTER_SINK_B_H */
