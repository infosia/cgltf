typedef enum cgltf_vrm_blendshape_group_presetName {
	cgltf_vrm_blendshape_group_presetName_unknown,
	cgltf_vrm_blendshape_group_presetName_neutral,
	cgltf_vrm_blendshape_group_presetName_a,
	cgltf_vrm_blendshape_group_presetName_i,
	cgltf_vrm_blendshape_group_presetName_u,
	cgltf_vrm_blendshape_group_presetName_e,
	cgltf_vrm_blendshape_group_presetName_o,
	cgltf_vrm_blendshape_group_presetName_blink,
	cgltf_vrm_blendshape_group_presetName_joy,
	cgltf_vrm_blendshape_group_presetName_angry,
	cgltf_vrm_blendshape_group_presetName_sorrow,
	cgltf_vrm_blendshape_group_presetName_fun,
	cgltf_vrm_blendshape_group_presetName_lookup,
	cgltf_vrm_blendshape_group_presetName_lookdown,
	cgltf_vrm_blendshape_group_presetName_lookleft,
	cgltf_vrm_blendshape_group_presetName_lookright,
	cgltf_vrm_blendshape_group_presetName_blink_l,
	cgltf_vrm_blendshape_group_presetName_blink_r,
} cgltf_vrm_blendshape_group_presetName;

typedef enum cgltf_vrm_firstperson_lookAtTypeName {
	cgltf_vrm_firstperson_lookAtTypeName_Bone,
	cgltf_vrm_firstperson_lookAtTypeName_BlendShape,
} cgltf_vrm_firstperson_lookAtTypeName;

typedef enum cgltf_vrm_humanoid_bone_bone {
	cgltf_vrm_humanoid_bone_bone_hips,
	cgltf_vrm_humanoid_bone_bone_leftUpperLeg,
	cgltf_vrm_humanoid_bone_bone_rightUpperLeg,
	cgltf_vrm_humanoid_bone_bone_leftLowerLeg,
	cgltf_vrm_humanoid_bone_bone_rightLowerLeg,
	cgltf_vrm_humanoid_bone_bone_leftFoot,
	cgltf_vrm_humanoid_bone_bone_rightFoot,
	cgltf_vrm_humanoid_bone_bone_spine,
	cgltf_vrm_humanoid_bone_bone_chest,
	cgltf_vrm_humanoid_bone_bone_neck,
	cgltf_vrm_humanoid_bone_bone_head,
	cgltf_vrm_humanoid_bone_bone_leftShoulder,
	cgltf_vrm_humanoid_bone_bone_rightShoulder,
	cgltf_vrm_humanoid_bone_bone_leftUpperArm,
	cgltf_vrm_humanoid_bone_bone_rightUpperArm,
	cgltf_vrm_humanoid_bone_bone_leftLowerArm,
	cgltf_vrm_humanoid_bone_bone_rightLowerArm,
	cgltf_vrm_humanoid_bone_bone_leftHand,
	cgltf_vrm_humanoid_bone_bone_rightHand,
	cgltf_vrm_humanoid_bone_bone_leftToes,
	cgltf_vrm_humanoid_bone_bone_rightToes,
	cgltf_vrm_humanoid_bone_bone_leftEye,
	cgltf_vrm_humanoid_bone_bone_rightEye,
	cgltf_vrm_humanoid_bone_bone_jaw,
	cgltf_vrm_humanoid_bone_bone_leftThumbProximal,
	cgltf_vrm_humanoid_bone_bone_leftThumbIntermediate,
	cgltf_vrm_humanoid_bone_bone_leftThumbDistal,
	cgltf_vrm_humanoid_bone_bone_leftIndexProximal,
	cgltf_vrm_humanoid_bone_bone_leftIndexIntermediate,
	cgltf_vrm_humanoid_bone_bone_leftIndexDistal,
	cgltf_vrm_humanoid_bone_bone_leftMiddleProximal,
	cgltf_vrm_humanoid_bone_bone_leftMiddleIntermediate,
	cgltf_vrm_humanoid_bone_bone_leftMiddleDistal,
	cgltf_vrm_humanoid_bone_bone_leftRingProximal,
	cgltf_vrm_humanoid_bone_bone_leftRingIntermediate,
	cgltf_vrm_humanoid_bone_bone_leftRingDistal,
	cgltf_vrm_humanoid_bone_bone_leftLittleProximal,
	cgltf_vrm_humanoid_bone_bone_leftLittleIntermediate,
	cgltf_vrm_humanoid_bone_bone_leftLittleDistal,
	cgltf_vrm_humanoid_bone_bone_rightThumbProximal,
	cgltf_vrm_humanoid_bone_bone_rightThumbIntermediate,
	cgltf_vrm_humanoid_bone_bone_rightThumbDistal,
	cgltf_vrm_humanoid_bone_bone_rightIndexProximal,
	cgltf_vrm_humanoid_bone_bone_rightIndexIntermediate,
	cgltf_vrm_humanoid_bone_bone_rightIndexDistal,
	cgltf_vrm_humanoid_bone_bone_rightMiddleProximal,
	cgltf_vrm_humanoid_bone_bone_rightMiddleIntermediate,
	cgltf_vrm_humanoid_bone_bone_rightMiddleDistal,
	cgltf_vrm_humanoid_bone_bone_rightRingProximal,
	cgltf_vrm_humanoid_bone_bone_rightRingIntermediate,
	cgltf_vrm_humanoid_bone_bone_rightRingDistal,
	cgltf_vrm_humanoid_bone_bone_rightLittleProximal,
	cgltf_vrm_humanoid_bone_bone_rightLittleIntermediate,
	cgltf_vrm_humanoid_bone_bone_rightLittleDistal,
	cgltf_vrm_humanoid_bone_bone_upperChest,
} cgltf_vrm_humanoid_bone_bone;

typedef enum cgltf_vrm_meta_allowedUserName {
	cgltf_vrm_meta_allowedUserName_OnlyAuthor,
	cgltf_vrm_meta_allowedUserName_ExplicitlyLicensedPerson,
	cgltf_vrm_meta_allowedUserName_Everyone,
} cgltf_vrm_meta_allowedUserName;

typedef enum cgltf_vrm_meta_violentUssageName {
	cgltf_vrm_meta_violentUssageName_Disallow,
	cgltf_vrm_meta_violentUssageName_Allow,
} cgltf_vrm_meta_violentUssageName;

typedef enum cgltf_vrm_meta_sexualUssageName {
	cgltf_vrm_meta_sexualUssageName_Disallow,
	cgltf_vrm_meta_sexualUssageName_Allow,
} cgltf_vrm_meta_sexualUssageName;

typedef enum cgltf_vrm_meta_commercialUssageName {
	cgltf_vrm_meta_commercialUssageName_Disallow,
	cgltf_vrm_meta_commercialUssageName_Allow,
} cgltf_vrm_meta_commercialUssageName;

typedef enum cgltf_vrm_meta_licenseName {
	cgltf_vrm_meta_licenseName_Redistribution_Prohibited,
	cgltf_vrm_meta_licenseName_CC0,
	cgltf_vrm_meta_licenseName_CC_BY,
	cgltf_vrm_meta_licenseName_CC_BY_NC,
	cgltf_vrm_meta_licenseName_CC_BY_SA,
	cgltf_vrm_meta_licenseName_CC_BY_NC_SA,
	cgltf_vrm_meta_licenseName_CC_BY_ND,
	cgltf_vrm_meta_licenseName_CC_BY_NC_ND,
	cgltf_vrm_meta_licenseName_Other,
} cgltf_vrm_meta_licenseName;


typedef struct cgltf_vrm_secondaryanimation_collidergroup_colliders {
	cgltf_float* offset; // [x, y, z]
	cgltf_float radius;
} cgltf_vrm_secondaryanimation_collidergroup_colliders;

typedef struct cgltf_vrm_secondaryanimation_spring {
	char* comment;
	cgltf_float stiffiness;
	cgltf_float gravityPower;
	cgltf_float* gravityDir; // [x, y, z]
	cgltf_float dragForce;
	cgltf_int center;
	cgltf_float hitRadius;
	cgltf_int* bones;
	cgltf_size bones_count;
	cgltf_int* colliderGroups;
	cgltf_size colliderGroups_count;
} cgltf_vrm_secondaryanimation_spring;

typedef struct cgltf_vrm_secondaryanimation_collidergroup {
	cgltf_int node;
	cgltf_vrm_secondaryanimation_collidergroup_colliders* colliders;
	cgltf_size colliders_count;
} cgltf_vrm_secondaryanimation_collidergroup;

typedef struct cgltf_vrm_secondaryanimation {
	cgltf_vrm_secondaryanimation_spring* boneGroups;
	cgltf_size boneGroups_count;
	cgltf_vrm_secondaryanimation_collidergroup* colliderGroups;
	cgltf_size colliderGroups_count;
} cgltf_vrm_secondaryanimation;

typedef struct cgltf_vrm_blendshape_bind {
	cgltf_int mesh;
	cgltf_int index;
	cgltf_float weight;
} cgltf_vrm_blendshape_bind;

typedef struct cgltf_vrm_blendshape_materialbind {
	char* materialName;
	char* propertyName;
	cgltf_float* targetValue;
	cgltf_size targetValue_count;
} cgltf_vrm_blendshape_materialbind;

typedef struct cgltf_vrm_blendshape_group {
	char* name;
	cgltf_vrm_blendshape_bind* binds;
	cgltf_size binds_count;
	cgltf_vrm_blendshape_materialbind* materialValues;
	cgltf_size materialValues_count;
	cgltf_bool isBinary;
} cgltf_vrm_blendshape_group;

typedef struct cgltf_vrm_blendshape {
	cgltf_vrm_blendshape_group* blendShapeGroups;
	cgltf_size blendShapeGroups_count;
} cgltf_vrm_blendshape;

typedef struct cgltf_vrm_firstperson_degreemap {
	cgltf_float* curve;
	cgltf_size curve_count;
	cgltf_float xRange;
	cgltf_float yRange;
} cgltf_vrm_firstperson_degreemap;

typedef struct cgltf_vrm_firstperson_meshannotation {
	cgltf_int mesh;
	char* firstPersonFlag;
} cgltf_vrm_firstperson_meshannotation;

typedef struct cgltf_vrm_firstperson {
	cgltf_int firstPersonBone;
	cgltf_float* firstPersonBoneOffset; // [x, y, z]
	cgltf_vrm_firstperson_meshannotation* meshAnnotations;
	cgltf_size meshAnnotations_count;
	cgltf_vrm_firstperson_degreemap lookAtHorizontalInner;
	cgltf_vrm_firstperson_degreemap lookAtHorizontalOuter;
	cgltf_vrm_firstperson_degreemap lookAtVerticalDown;
	cgltf_vrm_firstperson_degreemap lookAtVerticalUp;
} cgltf_vrm_firstperson;

typedef struct cgltf_vrm_humanoid_bone {
	cgltf_int node;
	cgltf_bool useDefaultValues;
	cgltf_float* min; // [x, y, z]
	cgltf_float* max; // [x, y, z]
	cgltf_float* center; // [x, y, z]
	cgltf_float axisLength;
} cgltf_vrm_humanoid_bone;

typedef struct cgltf_vrm_humanoid {
	cgltf_vrm_humanoid_bone* humanBones;
	cgltf_size humanBones_count;
	cgltf_float armStretch;
	cgltf_float legStretch;
	cgltf_float upperArmTwist;
	cgltf_float lowerArmTwist;
	cgltf_float upperLegTwist;
	cgltf_float lowerLegTwist;
	cgltf_float feetSpacing;
	cgltf_bool hasTranslationDoF;
} cgltf_vrm_humanoid;

typedef struct cgltf_vrm_material {
	char* name;
	char* shader;
	cgltf_int renderQueue;
	char** floatProperties_keys;
	cgltf_float* floatProperties_values;
	cgltf_size floatProperties_count;
	char** vectorProperties_keys;
	cgltf_float** vectorProperties_values;
	cgltf_size vectorProperties_count;
	char** textureProperties_keys;
	cgltf_int* textureProperties_values;
	cgltf_size textureProperties_count;
	char** keywordMap_keys;
	cgltf_bool* keywordMap_values;
	cgltf_size keywordMap_count;
	char** tagMap_keys;
	char** tagMap_values;
	cgltf_size tagMap_count;
} cgltf_vrm_material;

typedef struct cgltf_vrm_meta {
	char* title;
	char* version;
	char* author;
	char* contactInformation;
	char* reference;
	cgltf_int texture;
	char* otherPermissionUrl;
	char* otherLicenseUrl;
} cgltf_vrm_meta;

typedef struct cgltf_vrm {
	char* exporterVersion;
	char* specVersion;
	cgltf_vrm_meta meta;
	cgltf_vrm_humanoid humanoid;
	cgltf_vrm_firstperson firstPerson;
	cgltf_vrm_blendshape blendShapeMaster;
	cgltf_vrm_secondaryanimation secondaryAnimation;
	cgltf_vrm_material* materialProperties;
	cgltf_size materialProperties_count;
} cgltf_vrm;

static void cgltf_vrm_secondaryanimation_collidergroup_colliders_free(const struct cgltf_memory_options* memory, cgltf_vrm_secondaryanimation_collidergroup_colliders* data) {
	memory->free(memory->user_data, data->offset);
}
static void cgltf_vrm_secondaryanimation_spring_free(const struct cgltf_memory_options* memory, cgltf_vrm_secondaryanimation_spring* data) {
	memory->free(memory->user_data, data->comment);
	memory->free(memory->user_data, data->gravityDir);
	memory->free(memory->user_data, data->bones);
	memory->free(memory->user_data, data->colliderGroups);
}
static void cgltf_vrm_secondaryanimation_collidergroup_free(const struct cgltf_memory_options* memory, cgltf_vrm_secondaryanimation_collidergroup* data) {
	for (cgltf_size i = 0; i < data->colliders_count; i++) {
		cgltf_vrm_secondaryanimation_collidergroup_colliders_free(memory, &data->colliders[i]);
	}
	memory->free(memory->user_data, data->colliders);
}
static void cgltf_vrm_secondaryanimation_free(const struct cgltf_memory_options* memory, cgltf_vrm_secondaryanimation* data) {
	for (cgltf_size i = 0; i < data->boneGroups_count; i++) {
		cgltf_vrm_secondaryanimation_spring_free(memory, &data->boneGroups[i]);
	}
	memory->free(memory->user_data, data->boneGroups);
	for (cgltf_size i = 0; i < data->colliderGroups_count; i++) {
		cgltf_vrm_secondaryanimation_collidergroup_free(memory, &data->colliderGroups[i]);
	}
	memory->free(memory->user_data, data->colliderGroups);
}
static void cgltf_vrm_blendshape_bind_free(const struct cgltf_memory_options* memory, cgltf_vrm_blendshape_bind* data) {
	(void)memory;
	(void)data;
}
static void cgltf_vrm_blendshape_materialbind_free(const struct cgltf_memory_options* memory, cgltf_vrm_blendshape_materialbind* data) {
	memory->free(memory->user_data, data->materialName);
	memory->free(memory->user_data, data->propertyName);
	memory->free(memory->user_data, data->targetValue);
}
static void cgltf_vrm_blendshape_group_free(const struct cgltf_memory_options* memory, cgltf_vrm_blendshape_group* data) {
	memory->free(memory->user_data, data->name);
	for (cgltf_size i = 0; i < data->binds_count; i++) {
		cgltf_vrm_blendshape_bind_free(memory, &data->binds[i]);
	}
	memory->free(memory->user_data, data->binds);
	for (cgltf_size i = 0; i < data->materialValues_count; i++) {
		cgltf_vrm_blendshape_materialbind_free(memory, &data->materialValues[i]);
	}
	memory->free(memory->user_data, data->materialValues);
}
static void cgltf_vrm_blendshape_free(const struct cgltf_memory_options* memory, cgltf_vrm_blendshape* data) {
	for (cgltf_size i = 0; i < data->blendShapeGroups_count; i++) {
		cgltf_vrm_blendshape_group_free(memory, &data->blendShapeGroups[i]);
	}
	memory->free(memory->user_data, data->blendShapeGroups);
}
static void cgltf_vrm_firstperson_degreemap_free(const struct cgltf_memory_options* memory, cgltf_vrm_firstperson_degreemap* data) {
	memory->free(memory->user_data, data->curve);
}
static void cgltf_vrm_firstperson_meshannotation_free(const struct cgltf_memory_options* memory, cgltf_vrm_firstperson_meshannotation* data) {
	memory->free(memory->user_data, data->firstPersonFlag);
}
static void cgltf_vrm_firstperson_free(const struct cgltf_memory_options* memory, cgltf_vrm_firstperson* data) {
	memory->free(memory->user_data, data->firstPersonBoneOffset);
	for (cgltf_size i = 0; i < data->meshAnnotations_count; i++) {
		cgltf_vrm_firstperson_meshannotation_free(memory, &data->meshAnnotations[i]);
	}
	memory->free(memory->user_data, data->meshAnnotations);
	cgltf_vrm_firstperson_degreemap_free(memory, &data->lookAtHorizontalInner);
	cgltf_vrm_firstperson_degreemap_free(memory, &data->lookAtHorizontalOuter);
	cgltf_vrm_firstperson_degreemap_free(memory, &data->lookAtVerticalDown);
	cgltf_vrm_firstperson_degreemap_free(memory, &data->lookAtVerticalUp);
}
static void cgltf_vrm_humanoid_bone_free(const struct cgltf_memory_options* memory, cgltf_vrm_humanoid_bone* data) {
	memory->free(memory->user_data, data->min);
	memory->free(memory->user_data, data->max);
	memory->free(memory->user_data, data->center);
}
static void cgltf_vrm_humanoid_free(const struct cgltf_memory_options* memory, cgltf_vrm_humanoid* data) {
	for (cgltf_size i = 0; i < data->humanBones_count; i++) {
		cgltf_vrm_humanoid_bone_free(memory, &data->humanBones[i]);
	}
	memory->free(memory->user_data, data->humanBones);
}
static void cgltf_vrm_material_free(const struct cgltf_memory_options* memory, cgltf_vrm_material* data) {
	memory->free(memory->user_data, data->name);
	memory->free(memory->user_data, data->shader);
	for (cgltf_size i = 0; i < data->floatProperties_count; i++) {
		memory->free(memory->user_data, data->floatProperties_keys[i]);
	}
	memory->free(memory->user_data, data->floatProperties_keys);
	memory->free(memory->user_data, data->floatProperties_values);
	for (cgltf_size i = 0; i < data->vectorProperties_count; i++) {
		memory->free(memory->user_data, data->vectorProperties_keys[i]);
		memory->free(memory->user_data, data->vectorProperties_values[i]);
	}
	memory->free(memory->user_data, data->vectorProperties_keys);
	memory->free(memory->user_data, data->vectorProperties_values);
	for (cgltf_size i = 0; i < data->textureProperties_count; i++) {
		memory->free(memory->user_data, data->textureProperties_keys[i]);
	}
	memory->free(memory->user_data, data->textureProperties_keys);
	memory->free(memory->user_data, data->textureProperties_values);
	for (cgltf_size i = 0; i < data->keywordMap_count; i++) {
		memory->free(memory->user_data, data->keywordMap_keys[i]);
	}
	memory->free(memory->user_data, data->keywordMap_keys);
	memory->free(memory->user_data, data->keywordMap_values);
	for (cgltf_size i = 0; i < data->tagMap_count; i++) {
		memory->free(memory->user_data, data->tagMap_keys[i]);
		memory->free(memory->user_data, data->tagMap_values[i]);
	}
	memory->free(memory->user_data, data->tagMap_keys);
	memory->free(memory->user_data, data->tagMap_values);
}
static void cgltf_vrm_meta_free(const struct cgltf_memory_options* memory, cgltf_vrm_meta* data) {
	memory->free(memory->user_data, data->title);
	memory->free(memory->user_data, data->version);
	memory->free(memory->user_data, data->author);
	memory->free(memory->user_data, data->contactInformation);
	memory->free(memory->user_data, data->reference);
	memory->free(memory->user_data, data->otherPermissionUrl);
	memory->free(memory->user_data, data->otherLicenseUrl);
}
static void cgltf_vrm_free(const struct cgltf_memory_options* memory, cgltf_vrm* data) {
	memory->free(memory->user_data, data->exporterVersion);
	memory->free(memory->user_data, data->specVersion);
	cgltf_vrm_meta_free(memory, &data->meta);
	cgltf_vrm_humanoid_free(memory, &data->humanoid);
	cgltf_vrm_firstperson_free(memory, &data->firstPerson);
	cgltf_vrm_blendshape_free(memory, &data->blendShapeMaster);
	cgltf_vrm_secondaryanimation_free(memory, &data->secondaryAnimation);
	for (cgltf_size i = 0; i < data->materialProperties_count; i++) {
		cgltf_vrm_material_free(memory, &data->materialProperties[i]);
	}
	memory->free(memory->user_data, data->materialProperties);
}
