/* 
 *  Copyright 2011 Matthias Fuchs
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "Exception.h"
#include "ImageWrapper.h"

namespace stromx
{
    namespace core
    {
        ImageWrapper::ImageWrapper(const unsigned int bufferSize, uint8_t* const buffer)
          : m_width(0),
            m_height(0),
            m_stride(0),
            m_bufferSize(bufferSize),
            m_pixelType(NONE),
            m_data(0),
            m_buffer(buffer),
            m_variant(DataVariant::IMAGE)
        {
        }
        
        ImageWrapper::ImageWrapper()
          : m_width(0),
            m_height(0),
            m_stride(0),
            m_bufferSize(0),
            m_pixelType(NONE),
            m_data(0),
            m_buffer(0),
            m_variant(DataVariant::IMAGE)
        {
        }

        void ImageWrapper::setBuffer(uint8_t*const buffer, const unsigned int bufferSize)
        {
            m_bufferSize = bufferSize;
            m_buffer = buffer;
        }
        
        const unsigned int ImageWrapper::pixelSize() const
        {
            return depth(m_pixelType) * numChannels(m_pixelType);
        }
        
        void ImageWrapper::initialize(const unsigned int width, 
                                const unsigned int height, 
                                const unsigned int stride,
                                uint8_t*const data, 
                                const PixelType pixelType)
        {
            validate(width, height, stride, data, pixelType);
            
            m_width = width;
            m_height = height;
            m_stride = stride;
            m_data = data;
            m_pixelType = pixelType;
            m_variant = dataVariantFromPixelType(pixelType);
        }
        
        void ImageWrapper::validate(const unsigned int width,
                                    const unsigned int height,
                                    const unsigned int stride,
                                    const uint8_t*const data,
                                    const core::Image::PixelType pixelType) const
        {
            if(width == 0 || height == 0)
                return;
            
            // check row length
            if(width * depth(pixelType) * numChannels(pixelType) > stride)
                throw WrongArgument("Too small stride.");
            
            // check total data size
            unsigned int dataSize = stride * (height - 1) + width;
            if(data + dataSize > m_buffer + m_bufferSize)
                throw WrongArgument("Too small buffer.");
        }
        
        const core::DataVariant ImageWrapper::dataVariantFromPixelType(const core::Image::PixelType pixelType)
        {
            switch(pixelType)
            {
            case core::Image::NONE:
                return core::DataVariant::IMAGE;
            case core::Image::MONO_8:
                return core::DataVariant::MONO_8_IMAGE;
            case core::Image::BAYERBG_8:
                return core::DataVariant::BAYERBG_8_IMAGE;
            case core::Image::BAYERGB_8:
                return core::DataVariant::BAYERGB_8_IMAGE;
            case core::Image::RGB_24:
                return core::DataVariant::RGB_24_IMAGE;
            case core::Image::BGR_24:
                return core::DataVariant::BGR_24_IMAGE;
            default:
                throw core::WrongArgument("Unknown pixel type.");  
            }
        }
        
        const unsigned int ImageWrapper::valueSize() const
        {
            return Matrix::valueSize(valueType());
        }

        const stromx::core::Matrix::ValueType ImageWrapper::valueType() const
        {
            switch(m_pixelType)
            {
            case core::Image::NONE:
            case core::Image::MONO_8:
            case core::Image::BAYERBG_8:
            case core::Image::BAYERGB_8:
            case core::Image::RGB_24:
            case core::Image::BGR_24:
                return Matrix::UINT_8;
            default:
                throw core::WrongArgument("Unknown pixel type.");  
            }
        }

        void ImageWrapper::initialize(const unsigned int rows, const unsigned int cols, const unsigned int stride, uint8_t*const data, const stromx::core::Matrix::ValueType valueType)
        {
            validate(cols * Matrix::valueSize(valueType), rows, stride, data, NONE);
            
            m_width = cols * Matrix::valueSize(valueType);
            m_height = rows;
            m_stride = stride;
            m_data = data;
            m_pixelType = NONE;
            m_variant = dataVariantFromValueType(valueType);

        }
    }
}
