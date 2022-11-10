/*!
* \file PlotOptions.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/


#ifndef GRAFICI_GFX_PLOT_OPTIONS_H
#define GRAFICI_GFX_PLOT_OPTIONS_H

struct PlotOptions
{
    public:
    size_t segments{1}; /* use ~45 for polar plots */
    bool draw_background{true};
    Color background_color{black}; 
};

#endif /* GRAFICI_GFX_PLOT_OPTIONS_H */