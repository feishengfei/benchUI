/**
 ** @file max-getMax.cpp
 ** @author Cary.Zhang
 ** @par History:
 **    A001: Cary.Zhang, 2020-05-15, create file
 ** @par TestPoints:
 **   
 */

#include "Sample.h"

using std::string;
using namespace std;

void getInfo()
{
GLint my_attribs;
GLint my_uniform_components;
GLint my_vectors;
GLint my_uniform_blocks;
GLint my_output_components;
GLint my_units;
GLint my_counters;
GLint my_storage_blocks;
GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &my_attribs));
LOGI("GL_MAX_VERTEX_ATTRIBS = %d\n", my_attribs);
GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &my_uniform_components));
LOGI("GL_MAX_VERTEX_UNIFORM_COMPONENTS = %d\n", my_uniform_components);
GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &my_vectors));
LOGI("GL_MAX_VERTEX_UNIFORM_VECTORS = %d\n", my_vectors);
GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &my_uniform_blocks));
LOGI("GL_MAX_VERTEX_UNIFORM_BLOCKS = %d\n", my_uniform_blocks);
GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &my_output_components));
LOGI("GL_MAX_VERTEX_OUTPUT_COMPONENTS = %d\n", my_output_components);
GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &my_units));
LOGI("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = %d\n", my_units);
//GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTERS, &my_counters));
//LOGI("GL_MAX_VERTEX_ATOMIC_COUNTERS = %d\n", my_counters);
//GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, &my_storage_blocks));
//LOGI("GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS = %d\n", my_storage_blocks);

GLint my_3d_texture_size;
GLint my_texture_size;
GLint my_array_texture_layers;
GLint my_texture_lod_bias;
GLint my_cube_map_texture_size;
GLint my_renderbuffer_szie;
GLint my_viewport_dims;
GLint my_viewports;
GLint my_elements_indices;
GLint my_elements_vertices;
GLint my_vertex_attrib_relative_offset;
GLint my_vertex_attrib_bindings;
GLint my_texture_buffer_size;
GLint my_rectangle_texture_size;
GL_CHECK(glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE , &my_3d_texture_size));
LOGI("GL_MAX_3D_TEXTURE_SIZE = %d\n", my_3d_texture_size);
GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_SIZE , &my_texture_size));
LOGI("GL_MAX_TEXTURE_SIZE = %d\n", my_texture_size);
GL_CHECK(glGetIntegerv(GL_MAX_ARRAY_TEXTURE_LAYERS , &my_array_texture_layers));
LOGI("GL_MAX_ARRAY_TEXTURE_LAYERS = %d\n", my_array_texture_layers);
GL_CHECK(glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE , &my_cube_map_texture_size));
LOGI("GL_MAX_CUBE_MAP_TEXTURE_SIZE = %d\n", my_cube_map_texture_size);
GL_CHECK(glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE , &my_renderbuffer_szie));
LOGI("GL_MAX_RENDERBUFFER_SIZE = %d\n", my_renderbuffer_szie);
GL_CHECK(glGetIntegerv(GL_MAX_VIEWPORTS , &my_viewports));
LOGI("GL_MAX_VIEWPORTS = %d\n", my_viewports);
GL_CHECK(glGetIntegerv(GL_MAX_ELEMENTS_INDICES , &my_elements_indices));
LOGI("GL_MAX_ELEMENTS_INDICES = %d\n", my_elements_indices);
GL_CHECK(glGetIntegerv(GL_MAX_ELEMENTS_VERTICES , &my_elements_vertices));
LOGI("GL_MAX_ELEMENTS_VERTICES = %d\n", my_elements_vertices);
GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET , &my_vertex_attrib_relative_offset));
LOGI("GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET = %d\n", my_vertex_attrib_relative_offset);
GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS , &my_vertex_attrib_bindings));
LOGI("GL_MAX_VERTEX_ATTRIB_BINDINGS = %d\n", my_vertex_attrib_bindings);
GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE , &my_texture_buffer_size));
LOGI("GL_MAX_TEXTURE_BUFFER_SIZE = %d\n", my_texture_buffer_size);
GL_CHECK(glGetIntegerv(GL_MAX_RECTANGLE_TEXTURE_SIZE , &my_rectangle_texture_size));
LOGI("GL_MAX_RECTANGLE_TEXTURE_SIZE = %d\n", my_rectangle_texture_size);

GLint my_fragment_uniform_components;
GLint my_fragment_uniform_vectors;
GLint my_fragment_input_components;
GLint my_texture_image_units;
GLint my_min_program_texture_gather_offset;
GLint my_program_texture_gather_offset;
GLint my_fragment_atomic_counter_buffers;
GLint my_fragment_atomic_counters;
GLint my_fragment_shader_storage_blocks;
GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS , &my_fragment_uniform_components));
LOGI("GL_MAX_FRAGMENT_UNIFORM_COMPONENTS = %d\n", my_fragment_uniform_components);
GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS , &my_fragment_uniform_vectors));
LOGI("GL_MAX_FRAGMENT_UNIFORM_VECTORS = %d\n", my_fragment_uniform_vectors);
GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS , &my_fragment_input_components));
LOGI("GL_MAX_FRAGMENT_INPUT_COMPONENTS = %d\n", my_fragment_input_components);
GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS , &my_texture_image_units));
LOGI("GL_MAX_TEXTURE_IMAGE_UNITS = %d\n", my_texture_image_units);
GL_CHECK(glGetIntegerv(GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET , &my_min_program_texture_gather_offset));
LOGI("GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET = %d\n", my_min_program_texture_gather_offset);
GL_CHECK(glGetIntegerv(GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET , &my_program_texture_gather_offset ));
LOGI("GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET = %d\n", my_program_texture_gather_offset);
//GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS , &my_fragment_atomic_counter_buffers));
//LOGI("GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS = %d\n", my_fragment_atomic_counter_buffers);
//GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTERS , &my_fragment_atomic_counters));
//LOGI("GL_MAX_FRAGMENT_ATOMIC_COUNTERS = %d\n", my_fragment_atomic_counters);
//GL_CHECK(glGetIntegerv(GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS , &my_fragment_shader_storage_blocks));
//LOGI("GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS = %d\n", my_fragment_shader_storage_blocks);

GLint my_geometry_uniform_components;
GLint my_geometry_uniform_blocks;
GLint my_geometry_input_components;
GLint my_geometry_output_components;
GLint my_geometry_output_vertices;
GLint my_geometry_total_output_components;
GLint my_geometry_texture_image_units;
GLint my_geometry_shader_invocations;
GLint my_vertex_streams;
GLint my_geometry_atomic_counter_buffers;
GLint my_geometry_atomic_counters;
GLint my_geometry_shader_storage_blocks;
GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS , &my_geometry_uniform_components));
LOGI("GL_MAX_GEOMETRY_UNIFORM_COMPONENTS = %d\n", my_geometry_uniform_components);
GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS , &my_geometry_uniform_blocks));
LOGI("GL_MAX_GEOMETRY_UNIFORM_BLOCKS = %d\n", my_geometry_uniform_blocks);
GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_INPUT_COMPONENTS , &my_geometry_input_components));
LOGI("GL_MAX_GEOMETRY_INPUT_COMPONENTS = %d\n", my_geometry_input_components);
GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS , &my_geometry_output_components));
LOGI("GL_MAX_GEOMETRY_OUTPUT_COMPONENTS = %d\n", my_geometry_output_components);
GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES , &my_geometry_output_vertices));
LOGI("GL_MAX_GEOMETRY_OUTPUT_VERTICES = %d\n", my_geometry_output_vertices);
//GL_CHECK(glGetIntegerv(GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS , &my_geometry_shader_storage_blocks));
//LOGI("GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS = %d\n", my_geometry_shader_storage_blocks);

GLint my_clip_distances;
GLint my_color_texture_samples;
GLint my_combined_atomic_counters;
GLint my_combined_fragment_uniform_components;
GLint my_combined_geometry_uniform_components;
GLint my_combined_texture_image_units;
GLint my_combined_uniform_blocks;
GLint my_combined_vertex_uniform_components;
GLint my_depth_textures_samples;
GLint my_draw_buffers;
GLint my_dual_source_draw_buffers;

GL_CHECK(glGetIntegerv(GL_MAX_CLIP_DISTANCES , &my_clip_distances));
LOGI("GL_MAX_CLIP_DISTANCES = %d\n", my_clip_distances);
GL_CHECK(glGetIntegerv(GL_MAX_COLOR_TEXTURE_SAMPLES , &my_color_texture_samples));
LOGI("GL_MAX_COLOR_TEXTURE_SAMPLES = %d\n", my_color_texture_samples);
//GL_CHECK(glGetIntegerv(GL_MAX_COMBINED_ATOMIC_COUNTERS , &my_combined_atomic_counters));
//LOGI("GL_MAX_COMBINED_ATOMIC_COUNTERS = %d\n", my_combined_atomic_counters);
GL_CHECK(glGetIntegerv(GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS , &my_combined_fragment_uniform_components));
LOGI("GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = %d\n", my_combined_fragment_uniform_components);
GL_CHECK(glGetIntegerv(GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS , &my_combined_geometry_uniform_components));
LOGI("GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = %d\n", my_combined_geometry_uniform_components);
GL_CHECK(glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS , &my_combined_texture_image_units));
LOGI("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = %d\n", my_combined_texture_image_units);
GL_CHECK(glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS , &my_combined_uniform_blocks));
LOGI("GL_MAX_COMBINED_UNIFORM_BLOCKS = %d\n", my_combined_uniform_blocks);
GL_CHECK(glGetIntegerv(GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS , &my_combined_vertex_uniform_components));
LOGI("GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = %d\n", my_combined_vertex_uniform_components);
GL_CHECK(glGetIntegerv(GL_MAX_DEPTH_TEXTURE_SAMPLES , &my_depth_textures_samples));
LOGI("GL_MAX_DEPTH_TEXTURE_SAMPLES = %d\n", my_depth_textures_samples);
GL_CHECK(glGetIntegerv(GL_MAX_DRAW_BUFFERS , &my_draw_buffers));
LOGI("GL_MAX_DRAW_BUFFERS = %d\n", my_draw_buffers);
GL_CHECK(glGetIntegerv(GL_MAX_DUAL_SOURCE_DRAW_BUFFERS , &my_dual_source_draw_buffers));
LOGI("GL_MAX_DUAL_SOURCE_DRAW_BUFFERS = %d\n", my_dual_source_draw_buffers);

GLint my_tess_control_atomic_counters;
GLint my_tess_evaluation_atomic_counters;
GLint my_tess_control_shader_storage_blocks;
GLint my_tess_evaluation_shader_storage_blocks;
//GL_CHECK(glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS , &my_tess_control_atomic_counters));
//LOGI("GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS = %d\n", my_tess_control_atomic_counters);
//GL_CHECK(glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS , &my_tess_evaluation_atomic_counters));
//LOGI("GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS = %d\n", my_tess_evaluation_atomic_counters);
//GL_CHECK(glGetIntegerv(GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS , &my_tess_control_shader_storage_blocks));
//LOGI("GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS = %d\n", my_tess_control_shader_storage_blocks);
//GL_CHECK(glGetIntegerv(GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS , &my_tess_evaluation_shader_storage_blocks));
//LOGI("GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS = %d\n", my_tess_evaluation_shader_storage_blocks);

GLint my_framebuffer_width;
GLint my_framebuffer_height;
GLint my_framebuffer_layers;
GLint my_framebuffer_samples;
//GL_CHECK(glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH , &my_framebuffer_width));
//LOGI("GL_MAX_FRAMEBUFFER_WIDTH = %d\n", my_framebuffer_width);
//GL_CHECK(glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT , &my_framebuffer_height));
//LOGI("GL_MAX_FRAMEBUFFER_HEIGHT = %d\n", my_framebuffer_height);
//GL_CHECK(glGetIntegerv(GL_MAX_FRAMEBUFFER_LAYERS , &my_framebuffer_layers));
//LOGI("GL_MAX_FRAMEBUFFER_LAYERS = %d\n", my_framebuffer_layers);
//GL_CHECK(glGetIntegerv(GL_MAX_FRAMEBUFFER_SAMPLES , &my_framebuffer_samples));
//LOGI("GL_MAX_FRAMEBUFFER_SAMPLES = %d\n", my_framebuffer_samples);

GLint my_integer_samples;
GLint my_min_map_buffer_alignment;
GLint my_label_length;
GLint my_program_texel_offset;
GLint my_min_program_texel_offset;
GLint my_sample_mask_words;
GLint my_server_wait_timeout;
GLint my_shader_storage_buffer_bindings;
GL_CHECK(glGetIntegerv(GL_MAX_INTEGER_SAMPLES , &my_integer_samples));
LOGI("GL_MAX_INTEGER_SAMPLES = %d\n", my_integer_samples);
GL_CHECK(glGetIntegerv(GL_MIN_MAP_BUFFER_ALIGNMENT , &my_min_map_buffer_alignment));
LOGI("GL_MIN_MAP_BUFFER_ALIGNMENT = %d\n", my_min_map_buffer_alignment);
GL_CHECK(glGetIntegerv(GL_MAX_LABEL_LENGTH , &my_label_length));
LOGI("GL_MAX_LABEL_LENGTH = %d\n", my_label_length);
GL_CHECK(glGetIntegerv(GL_MAX_PROGRAM_TEXEL_OFFSET , &my_program_texel_offset));
LOGI("GL_MAX_PROGRAM_TEXEL_OFFSET = %d\n", my_program_texel_offset);
GL_CHECK(glGetIntegerv(GL_MIN_PROGRAM_TEXEL_OFFSET , &my_min_program_texel_offset));
LOGI("GL_MIN_PROGRAM_TEXEL_OFFSET = %d\n", my_min_program_texel_offset);
GL_CHECK(glGetIntegerv(GL_MAX_SAMPLE_MASK_WORDS , &my_sample_mask_words));
LOGI("GL_MAX_SAMPLE_MASK_WORDS = %d\n", my_sample_mask_words);
GL_CHECK(glGetIntegerv(GL_MAX_SERVER_WAIT_TIMEOUT , &my_server_wait_timeout));
LOGI("GL_MAX_SERVER_WAIT_TIMEOUT = %d\n", my_server_wait_timeout);
//GL_CHECK(glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS , &my_shader_storage_buffer_bindings));
//LOGI("GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS = %d\n", my_shader_storage_buffer_bindings);

GLint my_uniform_buffer_bindings;
GLint my_uniform_block_size;
GLint my_uniform_locations;
GLint my_varying_components;
GLint my_varying_vectors;
GLint my_varying_floats;
GLint my_element_index;
GL_CHECK(glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS , &my_uniform_buffer_bindings));
LOGI("GL_MAX_UNIFORM_BUFFER_BINDINGS = %d\n", my_uniform_buffer_bindings);
GL_CHECK(glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE , &my_uniform_block_size));
LOGI("GL_MAX_UNIFORM_BLOCK_SIZE = %d\n", my_uniform_block_size);
GL_CHECK(glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS , &my_uniform_locations));
LOGI("GL_MAX_UNIFORM_LOCATIONS = %d\n", my_uniform_locations);
GL_CHECK(glGetIntegerv(GL_MAX_VARYING_COMPONENTS , &my_varying_components));
LOGI("GL_MAX_VARYING_COMPONENTS = %d\n", my_varying_components);
GL_CHECK(glGetIntegerv(GL_MAX_VARYING_VECTORS , &my_varying_vectors));
LOGI("GL_MAX_VARYING_VECTORS = %d\n", my_varying_vectors);
GL_CHECK(glGetIntegerv(GL_MAX_VARYING_FLOATS ,&my_varying_floats));
LOGI("GL_MAX_VARYING_FLOATS = %d\n", my_varying_floats);
GL_CHECK(glGetIntegerv(GL_MAX_ELEMENT_INDEX , &my_element_index));
LOGI("GL_MAX_ELEMENT_INDEX = %d\n", my_element_index);
}

void Sample::test() {
    getInfo();
}

int main(int argc, char **argv){
    Sample sample(__FILE__, GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE, argc,argv);
    sample.test();
    return 0;
}
