#include <stdio.h>
#include <assert.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "core/input.h"
#include "core/mem.h"
#include "core/maths.h"

#include "renderer/renderer.h"
#include "renderer/buffer.h"
#include "renderer/shader.h"
#include "renderer/model.h"

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#include "tinyobj_loader_c.h"

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, 
                            GLsizei length, const char *message, const void *user) {
    printf("%s\n", message);
}

static void GetFileData(void* ctx, const char* filename, const int is_mtl,
                          const char* obj_filename, char** data, size_t* len) {
    (void)ctx;

    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Failed to read file: %s\n", filename);
        UNREACHABLE;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buf = AllocMem(size + 1, MEMORY_TAG_TEMP);

    size_t read = fread(buf, sizeof(char), size, f);
    assert(read == size);

    buf[size] = '\0';

    fclose(f);

    *data = buf;
    *len = size;
}


model *LoadObj(char *path) {
    tinyobj_attrib_t attrib;
    tinyobj_shape_t* shapes = NULL;
    size_t numShapes;
    tinyobj_material_t* materials = NULL;
    size_t numMaterials;

    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
    int ret = tinyobj_parse_obj(&attrib, &shapes, &numShapes, &materials, &numMaterials, path, GetFileData, NULL, flags);
    if (ret != TINYOBJ_SUCCESS) {
        printf("Failed to load obj: %s\n", path);
        return NULL;
    }

    printf("# of shapes    = %d\n", (int)numShapes);
    printf("# of materials = %d\n", (int)numMaterials);

    f32 *vertices = (f32 *)AllocMem(3 * attrib.num_vertices * sizeof(f32), MEMORY_TAG_TEMP);
    memcpy(vertices, attrib.vertices, attrib.num_vertices * 3 * sizeof(f32));

    i32 totalIndices = 0;
    for (i32 i = 0; i < numShapes; i++) {
        totalIndices += shapes[i].length;
    }

    u32 *indices = (u32 *)malloc(totalIndices * sizeof(u32));
    i32 indexOffset = 0;
    for (i32 i = 0; i < numShapes; i++) {
        i32 numFaces = shapes[i].length;
        for (i32 j = 0; j < numFaces; j++) {
            tinyobj_vertex_index_t idx = attrib.faces[indexOffset++];
            indices[indexOffset - 1] = idx.v_idx;
        }
    }

    vert_3d *verts = (vert_3d *)AllocMem(sizeof(vert_3d) * attrib.num_vertices, MEMORY_TAG_TEMP);
    for (i32 i = 0; i < attrib.num_vertices; i++) {
        verts[i].position.x = vertices[i * 3 + 0];
        verts[i].position.y = vertices[i * 3 + 1];
        verts[i].position.z = vertices[i * 3 + 2];

        verts[i].color = v3(0.0f, 0.0f, 1.0f);
    }

    model *m = LoadModel(verts, attrib.num_vertices, indices, totalIndices);
    return m;
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);  

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Solaris", NULL, NULL);
    assert(window);

    glfwMakeContextCurrent(window);
    gladLoadGL((GLADloadfunc)glfwGetProcAddress);

    int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
        glDebugMessageCallback(glDebugOutput, NULL);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE); 
    }

    memory_arena *stateArena = InitializeMemoryArena(1024 * 1024 * 4);

    InitializeInput(window, stateArena);
    InitializeRenderer(stateArena);

    vert_3d vertices[4] = {
        {v3(-1.0f, 0.0f, 1.0f), v3(1.0f, 0.0f, 0.0f)},
        {v3(1.0f, 0.0f, 1.0f), v3(0.0f, 1.0f, 0.0f)},
        {v3(1.0f, 0.0f, -1.0f), v3(0.0f, 0.0f, 1.0f)},
        {v3(-1.0f, 0.0f, -1.0f), v3(1.0f, 1.0f, 1.0f)},
    };

    u32 indices[6] = {
        0, 1, 2,
        2, 3, 0,
    };

    model *testModel = LoadObj("res/models/sphere.obj");
    // model *testModel = LoadModel(vertices, 4, indices, 6);
    shader *testShader = LoadShader("res/shaders/test.vert", "res/shaders/test.frag", 0);

    mat4 view = Mat4LookAt(v3(0.0f, 3.0f, 3.0f), Vec3Zero(), Vec3Up());
    mat4 projection = Mat4Perspective(DegToRed(45.0f), 1280.0f / 720.0f, 0.01f, 100.0f);

    glUseProgram(testShader->handle);
    u32 projLocation = glGetUniformLocation(testShader->handle, "projection");
    u32 viewLocation = glGetUniformLocation(testShader->handle, "view");
    u32 modelLocation = glGetUniformLocation(testShader->handle, "model");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, projection.data);
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, view.data);

    glBindVertexArray(testModel->handle);
    glBindBuffer(GL_ARRAY_BUFFER, testModel->vertex->handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, testModel->index->handle);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        f32 angle = glfwGetTime();
        quat q = QuatFromAxisAngle(Vec3Up(), angle, true);
        mat4 scale = Mat4Scale(v3(1.0f, 1.0f, 1.0f));
        mat4 rotation = QuatToRotationMatrix(q, Vec3Zero());
        mat4 translation = Mat4Translation(v3(1.0f, -1.0f, -2.0f));
        mat4 model = Mat4Mul(translation, Mat4Mul(rotation, scale));
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model.data);

        glUseProgram(testShader->handle);
        glDrawElements(GL_TRIANGLES, testModel->indexCount, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        InputUpdate();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}