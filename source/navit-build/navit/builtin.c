
void	module_font_freetype_init(void);
void	module_graphics_gtk_drawing_area_init(void);
void	module_graphics_opengl_init(void);
void	module_gui_gtk_init(void);
void	module_vehicle_gpsd_init(void);
void	module_speech_cmdline_init(void);
void	module_graphics_null_init(void);
void	module_osd_core_init(void);
void	module_vehicle_demo_init(void);
void	module_vehicle_file_init(void);
void	module_gui_internal_init(void);
void	module_map_binfile_init(void);
void	module_map_filter_init(void);
void	module_map_mg_init(void);
void	module_map_shapefile_init(void);
void	module_map_textfile_init(void);
void	module_map_csv_init(void);
extern void builtin_init(void); 
void builtin_init(void) { 
    
module_font_freetype_init();
module_graphics_gtk_drawing_area_init();
module_graphics_opengl_init();
module_gui_gtk_init();
module_vehicle_gpsd_init();
module_speech_cmdline_init();
module_graphics_null_init();
module_osd_core_init();
module_vehicle_demo_init();
module_vehicle_file_init();
module_gui_internal_init();
module_map_binfile_init();
module_map_filter_init();
module_map_mg_init();
module_map_shapefile_init();
module_map_textfile_init();
module_map_csv_init();
}
