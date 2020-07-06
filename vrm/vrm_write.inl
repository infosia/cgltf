static void cgltf_write_vrm_secondaryanimation_collidergroup_colliders(cgltf_write_context* context, const cgltf_vrm_secondaryanimation_collidergroup_colliders* data) {
	cgltf_write_line(context, "{");
	if (data->offset_count > 0) {
		cgltf_write_floatarrayprop(context, "offset", data->offset, 3);
	}
	cgltf_write_floatprop(context, "radius", data->radius, 0);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_secondaryanimation_spring(cgltf_write_context* context, const cgltf_vrm_secondaryanimation_spring* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "comment", data->comment);
	cgltf_write_floatprop(context, "stiffiness", data->stiffiness, 0);
	cgltf_write_floatprop(context, "gravityPower", data->gravityPower, 0);
	if (data->gravityDir_count > 0) {
		cgltf_write_floatarrayprop(context, "gravityDir", data->gravityDir, 3);
	}
	cgltf_write_floatprop(context, "dragForce", data->dragForce, 0);
	cgltf_write_intprop(context, "center", data->center, 0);
	cgltf_write_floatprop(context, "hitRadius", data->hitRadius, 0);
	cgltf_write_intarrayprop(context, "bones", data->bones, data->bones_count);
	cgltf_write_intarrayprop(context, "colliderGroups", data->colliderGroups, data->colliderGroups_count);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_secondaryanimation_collidergroup(cgltf_write_context* context, const cgltf_vrm_secondaryanimation_collidergroup* data) {
	cgltf_write_line(context, "{");
	cgltf_write_intprop(context, "node", data->node, 0);
	cgltf_write_line(context, "\"colliders\": [");
	for (cgltf_size i = 0; i < data->colliders_count; ++i) {
		cgltf_write_vrm_secondaryanimation_collidergroup_colliders(context, data->colliders + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_secondaryanimation(cgltf_write_context* context, const cgltf_vrm_secondaryanimation* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "\"boneGroups\": [");
	for (cgltf_size i = 0; i < data->boneGroups_count; ++i) {
		cgltf_write_vrm_secondaryanimation_spring(context, data->boneGroups + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "\"colliderGroups\": [");
	for (cgltf_size i = 0; i < data->colliderGroups_count; ++i) {
		cgltf_write_vrm_secondaryanimation_collidergroup(context, data->colliderGroups + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_blendshape_bind(cgltf_write_context* context, const cgltf_vrm_blendshape_bind* data) {
	cgltf_write_line(context, "{");
	cgltf_write_intprop(context, "mesh", data->mesh, 0);
	cgltf_write_intprop(context, "index", data->index, 0);
	cgltf_write_floatprop(context, "weight", data->weight, 0);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_blendshape_materialbind(cgltf_write_context* context, const cgltf_vrm_blendshape_materialbind* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "materialName", data->materialName);
	cgltf_write_strprop(context, "propertyName", data->propertyName);
	cgltf_write_floatarrayprop(context, "targetValue", data->targetValue, data->targetValue_count);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_blendshape_group(cgltf_write_context* context, const cgltf_vrm_blendshape_group* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "name", data->name);
	cgltf_write_strprop(context, "presetName", cgltf_vrm_blendshape_group_presetName_to_str(data->presetName));
	cgltf_write_line(context, "\"binds\": [");
	for (cgltf_size i = 0; i < data->binds_count; ++i) {
		cgltf_write_vrm_blendshape_bind(context, data->binds + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "\"materialValues\": [");
	for (cgltf_size i = 0; i < data->materialValues_count; ++i) {
		cgltf_write_vrm_blendshape_materialbind(context, data->materialValues + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_boolprop_optional(context, "isBinary", data->isBinary, 0);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_blendshape(cgltf_write_context* context, const cgltf_vrm_blendshape* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "\"blendShapeGroups\": [");
	for (cgltf_size i = 0; i < data->blendShapeGroups_count; ++i) {
		cgltf_write_vrm_blendshape_group(context, data->blendShapeGroups + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_firstperson_degreemap(cgltf_write_context* context, const cgltf_vrm_firstperson_degreemap* data) {
	cgltf_write_line(context, "{");
	cgltf_write_floatarrayprop(context, "curve", data->curve, data->curve_count);
	cgltf_write_floatprop(context, "xRange", data->xRange, 0);
	cgltf_write_floatprop(context, "yRange", data->yRange, 0);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_firstperson_meshannotation(cgltf_write_context* context, const cgltf_vrm_firstperson_meshannotation* data) {
	cgltf_write_line(context, "{");
	cgltf_write_intprop(context, "mesh", data->mesh, 0);
	cgltf_write_strprop(context, "firstPersonFlag", data->firstPersonFlag);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_firstperson(cgltf_write_context* context, const cgltf_vrm_firstperson* data) {
	cgltf_write_line(context, "{");
	cgltf_write_intprop(context, "firstPersonBone", data->firstPersonBone, 0);
	if (data->firstPersonBoneOffset_count > 0) {
		cgltf_write_floatarrayprop(context, "firstPersonBoneOffset", data->firstPersonBoneOffset, 3);
	}
	cgltf_write_line(context, "\"meshAnnotations\": [");
	for (cgltf_size i = 0; i < data->meshAnnotations_count; ++i) {
		cgltf_write_vrm_firstperson_meshannotation(context, data->meshAnnotations + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_strprop(context, "lookAtTypeName", cgltf_vrm_firstperson_lookAtTypeName_to_str(data->lookAtTypeName));
	cgltf_write_line(context, "\"lookAtHorizontalInner\": ");
	cgltf_write_vrm_firstperson_degreemap(context, &data->lookAtHorizontalInner);
	cgltf_write_line(context, "\"lookAtHorizontalOuter\": ");
	cgltf_write_vrm_firstperson_degreemap(context, &data->lookAtHorizontalOuter);
	cgltf_write_line(context, "\"lookAtVerticalDown\": ");
	cgltf_write_vrm_firstperson_degreemap(context, &data->lookAtVerticalDown);
	cgltf_write_line(context, "\"lookAtVerticalUp\": ");
	cgltf_write_vrm_firstperson_degreemap(context, &data->lookAtVerticalUp);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_humanoid_bone(cgltf_write_context* context, const cgltf_vrm_humanoid_bone* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "bone", cgltf_vrm_humanoid_bone_bone_to_str(data->bone));
	cgltf_write_intprop(context, "node", data->node, 0);
	cgltf_write_boolprop_optional(context, "useDefaultValues", data->useDefaultValues, 0);
	if (data->min_count > 0) {
		cgltf_write_floatarrayprop(context, "min", data->min, 3);
	}
	if (data->max_count > 0) {
		cgltf_write_floatarrayprop(context, "max", data->max, 3);
	}
	if (data->center_count > 0) {
		cgltf_write_floatarrayprop(context, "center", data->center, 3);
	}
	cgltf_write_floatprop(context, "axisLength", data->axisLength, 0);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_humanoid(cgltf_write_context* context, const cgltf_vrm_humanoid* data) {
	cgltf_write_line(context, "{");
	cgltf_write_line(context, "\"humanBones\": [");
	for (cgltf_size i = 0; i < data->humanBones_count; ++i) {
		cgltf_write_vrm_humanoid_bone(context, data->humanBones + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_floatprop(context, "armStretch", data->armStretch, 0);
	cgltf_write_floatprop(context, "legStretch", data->legStretch, 0);
	cgltf_write_floatprop(context, "upperArmTwist", data->upperArmTwist, 0);
	cgltf_write_floatprop(context, "lowerArmTwist", data->lowerArmTwist, 0);
	cgltf_write_floatprop(context, "upperLegTwist", data->upperLegTwist, 0);
	cgltf_write_floatprop(context, "lowerLegTwist", data->lowerLegTwist, 0);
	cgltf_write_floatprop(context, "feetSpacing", data->feetSpacing, 0);
	cgltf_write_boolprop_optional(context, "hasTranslationDoF", data->hasTranslationDoF, 0);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_material(cgltf_write_context* context, const cgltf_vrm_material* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "name", data->name);
	cgltf_write_strprop(context, "shader", data->shader);
	cgltf_write_intprop(context, "renderQueue", data->renderQueue, 0);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm_meta(cgltf_write_context* context, const cgltf_vrm_meta* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "title", data->title);
	cgltf_write_strprop(context, "version", data->version);
	cgltf_write_strprop(context, "author", data->author);
	cgltf_write_strprop(context, "contactInformation", data->contactInformation);
	cgltf_write_strprop(context, "reference", data->reference);
	cgltf_write_intprop(context, "texture", data->texture, 0);
	cgltf_write_strprop(context, "allowedUserName", cgltf_vrm_meta_allowedUserName_to_str(data->allowedUserName));
	cgltf_write_strprop(context, "violentUssageName", cgltf_vrm_meta_violentUssageName_to_str(data->violentUssageName));
	cgltf_write_strprop(context, "sexualUssageName", cgltf_vrm_meta_sexualUssageName_to_str(data->sexualUssageName));
	cgltf_write_strprop(context, "commercialUssageName", cgltf_vrm_meta_commercialUssageName_to_str(data->commercialUssageName));
	cgltf_write_strprop(context, "otherPermissionUrl", data->otherPermissionUrl);
	cgltf_write_strprop(context, "licenseName", cgltf_vrm_meta_licenseName_to_str(data->licenseName));
	cgltf_write_strprop(context, "otherLicenseUrl", data->otherLicenseUrl);
	cgltf_write_line(context, "}");
}
static void cgltf_write_vrm(cgltf_write_context* context, const cgltf_vrm* data) {
	cgltf_write_line(context, "{");
	cgltf_write_strprop(context, "exporterVersion", data->exporterVersion);
	cgltf_write_strprop(context, "specVersion", data->specVersion);
	cgltf_write_line(context, "\"meta\": ");
	cgltf_write_vrm_meta(context, &data->meta);
	cgltf_write_line(context, "\"humanoid\": ");
	cgltf_write_vrm_humanoid(context, &data->humanoid);
	cgltf_write_line(context, "\"firstPerson\": ");
	cgltf_write_vrm_firstperson(context, &data->firstPerson);
	cgltf_write_line(context, "\"blendShapeMaster\": ");
	cgltf_write_vrm_blendshape(context, &data->blendShapeMaster);
	cgltf_write_line(context, "\"secondaryAnimation\": ");
	cgltf_write_vrm_secondaryanimation(context, &data->secondaryAnimation);
	cgltf_write_line(context, "\"materialProperties\": [");
	for (cgltf_size i = 0; i < data->materialProperties_count; ++i) {
		cgltf_write_vrm_material(context, data->materialProperties + i);
	}
	cgltf_write_line(context, "]");
	cgltf_write_line(context, "}");
}