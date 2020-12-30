<?xml version="1.0"?><doc>
<members>
<member name="T:Material" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\Material.h" line="5">
\struct Material
Structure for storing material information read from an OBJ MTL file.
</member>
<member name="F:Material.d" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\Material.h" line="13">
the focus of the specular highlight.
Specify the dissolve for the current model. "factor" is the amount this material dissolves
into the background. A factor of 1.0 is fully opaque.This is the default when a new material
is created. A factor of 0.0 is fully dissolved(completely transparent).
</member>
<member name="F:Material.illum" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\Material.h" line="20">
Illumination model used for the material
0 Color on and Ambient off
1 Color on and Ambient on
2 Highlight on
3 Reflection on and Ray trace on
4 Transparency: Glass on
Reflection : Ray trace on
5 Reflection : Fresnel on and Ray trace on
6 Transparency : Refraction on
Reflection : Fresnel off and Ray trace on
7 Transparency : Refraction on
Reflection : Fresnel on and Ray trace on
8 Reflection on and Ray trace off
9 Transparency : Glass on
Reflection : Ray trace off
10 Casts shadows onto invisible surfaces
</member>
<member name="T:Vertex" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\Vertex.h" line="1">
\struct Vertex
A dedicated structure for storing the position of a 3D vertex (point).
</member>
<member name="T:Face" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\Face.h" line="5">
\struct Face
Define indices of vertices, normals, and textures for a face.
</member>
<member name="T:TextureCoord" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\Texture.h" line="1">
\struct TextureCoord
Structure for storing 2D texture coordinates
</member>
<member name="T:BoundingBox" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\BoundingBox.h" line="1">
\struct BoundingBox
Define the bounds along x, y, z axes, i.e., AABB
</member>
<member name="T:Vector3" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\Vector3D.h" line="3">
\struct Vector3
Structure for storing a 3D vector.
</member>
<member name="T:DisplayMode" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="19">
\enum DisplayMode
\brief Enumeration for different display modes.

</member>
<member name="T:ObjModel" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="24">
\class ObjModel
\brief A class for parsing and drawing OBJ 3D models.

</member>
<member name="M:ObjModel.ReadFile(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="33">
Read the OBJ and MTL files.
\param fileName Name of the OBJ file
</member>
<member name="M:ObjModel.GetVertices" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="39">
Get all the vertices of the mesh
\return An STL vector that contains all the vertices of the mesh.
</member>
<member name="M:ObjModel.GetNormals" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="43">
Get all the normals of the mesh
\return An STL vector that contains all the normals of the mesh.
</member>
<member name="M:ObjModel.GetFaces" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="47">
Get all the faces of the mesh
\return An STL vector that contains all the faces of the mesh.
</member>
<member name="M:ObjModel.GetMaterialNames" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="51">
Get all the material names of the mesh
\return An STL vector that contains all the material names of the mesh.
</member>
<member name="M:ObjModel.GetBoundingBox" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="55">
Get the AABB bounding box of the mesh.
</member>
<member name="M:ObjModel.SetDisplayMode(DisplayMode)" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="58">
Set display mode
\param displayMode Displaymode with values of Point, WireFrame, or Filled
</member>
<member name="M:ObjModel.Reset" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="62">
Reset the program.
Clear all the data structures for the mesh.  Initialize the bounding box 
</member>
<member name="M:ObjModel.GetCenter" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="66">
Get the center of the boundig box.
\return Center of the bounding box.
</member>
<member name="M:ObjModel.GetSize" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="70">
Get the size of the bounding box.
\return Size of the bounding box.
</member>
<member name="M:ObjModel.DrawMaterials(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;,System.Boolean)" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\ObjModel.h" line="94">
A function to draw different materials.
@param mtlName is the name of the material.
@param opaque whether the material is opaque or not
</member>
<member name="T:Signal" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\TrafficLight.h" line="4">
\struct Signal
Structure for storing traffic signal types
</member>
<member name="T:TrafficLight" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\TrafficLight.h" line="8">
\class TrafficLight
A Class for a traffic light
</member>
<member name="M:TrafficLight.ReadFile(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\TrafficLight.h" line="17">
Read the OBJ and MTL files.  Initialize the material values.
\param fileName Name of the OBJ file
</member>
<member name="M:TrafficLight.setMaterials" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\TrafficLight.h" line="21">
Initialize values of redOn, redOff, yellowOn, yellowOff, greenOn, and greenOff.
</member>
<member name="M:TrafficLight.setSignal(Signal)" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\TrafficLight.h" line="24">
Set the current signal of the traffic light.
\param signal The new signal of the traffic light.
</member>
<member name="F:TrafficLight.redOn" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\TrafficLight.h" line="29">
The material values for each signal on and off.  Note by default, private members are not shown
in Doxygen, but it can be enabled by checking EXTRACT_PRIVATE tag.
</member>
<member name="M:printString(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\utility.h" line="12">
Display text at the current raster position using font GLUT_BITMAP_9_BY_15.
\param str String to be displayed.
</member>
<member name="M:printLargeString(std.basic_string&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte,std.char_traits{System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte},std.allocator&lt;System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte&gt;&gt;)" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\utility.h" line="16">
Display text at the current raster position using font GLUT_BITMAP_HELVETICA_18.
\param str String to be displayed.
</member>
<member name="M:computeRotatedVector(Vector3,System.Single)" decl="true" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\utility.h" line="20">
Compute a Vector3 rotated around y axis based on an input Vector3 and an angle.
\param input Input Vector3
\param angle Angle of rotation
\return Resulting Vector3 generated by rotating input around y axis for the angle.
</member>
<member name="M:reshape(System.Int32,System.Int32)" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="50">
Update the small viewports' size automatically.
\param w Width of the OpenGL window
\param h Height of the OpenGL window
</member>
<member name="M:specialKey(System.Int32,System.Int32,System.Int32)" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="60">
Callback function for special keys.
\param key ASCII code of the key pressed.
\param x X coordinate of the mouse cursor when the key is pressed.
\param y Y coordinate of the mouse cursor when the key is pressed.
</member>
<member name="M:drawScene" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="92">
Function to draw the entire scene.
</member>
<member name="M:init" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="123">
Initialization.
Set up lighting, generate display lists for the surveillance camera, 
car, and terrain.
</member>
<member name="M:display" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="219">
Display callback.
Displays 4 viewports.  For for each viewport, set up position and size, projection, 
and camera (ModelView matrix).
</member>
<member name="M:keyboard(System.Byte,System.Int32,System.Int32)" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="255">
Keyboard callback
Handle regular key presses, and for P2, "r" for reset, "b" for break, and escape for quit.
</member>
<member name="M:update" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="275">
Updates the dynamic objects.
Update the car position and traffic signals.
</member>
<member name="M:timer(System.Int32)" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="284">
Set the interval between updates.
\param miliseconds is the number of miliseconds passed before this function is called.  It is the third
parameter of glutTimerFunc().
</member>
<member name="M:main(System.Int32,System.SByte!System.Runtime.CompilerServices.IsSignUnspecifiedByte**)" decl="false" source="D:\Documents\Courses\ODU\MSIM 641\2020\Fall\Programming Assignments\P2\Transportation - Base\Project\Project\src\main.cpp" line="294">
Main function
GLUT initialization, load 3D models, and register GLUT callbacks.
</member>
</members>
</doc>