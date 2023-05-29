#
#  Be sure to run `pod spec lint LetsviewMacSDK.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see https://guides.cocoapods.org/syntax/podspec.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
# pod trunk push LetsviewMacSDK.podspec --allow-warnings --skip-import-validation --verbose

Pod::Spec.new do |spec|

  spec.name         = "LetsviewMacSDK"
  spec.version      = "1.0.1"
  spec.summary      = "A short description of LetsviewMacSDK."

  spec.description  = "letsviewSDK"

  spec.homepage     = "https://letsview.com/sdk"

 spec.license      = { :type => "Commercial", :text => "©2023 Wangxutech.com"}

  spec.author      = { "wangxutech" => "moblie@wangxutech.com" }

     spec.source       = { :git => "https://github.com/WangXuTechSDK/LetsviewMacSDK.git", :tag => spec.version.to_s }



    spec.platform = :osx
    spec.osx.deployment_target = "10.15"
    spec.xcconfig = {
      'CLANG_CXX_LANGUAGE_STANDARD' => 'c++14',
      'CLANG_CXX_LIBRARY' => 'libc++'
  }
    spec.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-lObjC' }
        spec.swift_version = ['5.0', '5.1', '5.2','5.3']

  spec.vendored_frameworks ='framework/*.{framework}'

    spec.libraries = 'c++', 'z', 'iconv'
    spec.frameworks = 'VideoToolbox', 'CoreMedia', 'AudioToolbox', 'Cocoa'
      spec.requires_arc = true


end
