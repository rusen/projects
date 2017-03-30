function output = lsd(im, varargin)
% LSD Line Segment Detector
%   This is a LSD Wrapper for matlab.
%
%   Input: n-by-m single channel (grayscale) image. If class is not 'uint8'
%       then converted by mat2gray(im)
%
%   Parameters:
%    scale	Scale image by Gaussian filter before processing.
% 		'scale' is double, range [0,inf], default value 0.8
%    sigma_coef	Sigma for Gaussian filter is computed as sigma_coef/scale.
% 		'sigma_coef' is double, range [0,inf], default value 0.6
%    quant	Bound to quantization error on the gradient norm.
% 		'quant' is double, range [0,inf], default value 2
%    ang_th	Gradient angle tolerance in degrees.
% 		'ang_th' is double, range [0,180], default value 22.5
%    eps	Detection threshold, -log10(max. NFA)
% 		'eps' is double, range [-inf,inf], default value 0
%    density_th	Minimal density of region points in a rectangle to be
%    accepted.
% 		'density_th' is double, range [0,1], default value 0.7
%    n_bins	Number of bins in 'ordering' of gradient modulus.
% 		'n_bins' is integer, range [1,inf], default value 1024
%    max_grad	Gradient modulus in the highest bin.
% 		'max_grad' is double, range [1,inf], default value 255
%    reg	Output image showing pixels used by each detection. Scaled
%    size. epsfile	Output line segments into EPS file 'epsfile'. svgfile
%    Output line segments into SVG file 'svgfile'. width	LS width used
%    in EPS and SVG files. If <=0, use detected values.
% 		'width' is double, range [-inf,inf], default value 1.5
%
%  Output:
%   Line Segment output k-by-4 matrix having start end points of
%   lines and their widths (x1,y1,x2,y2,width)
%
%  Sample Run:
%   im = imread('image.tif');
%   greench = im(:,:,2);
%   output = lsd(greench, 'scale', 0.8, 'quant', 2);
%   figure, imshow(uint8(255*mat2gray(greench))), hold on;
%   for i = 1:size(output,1)
%         xy = [output(i,1), output(i,2); output(i,3), output(i,4)];
%         plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
%   end
%   hold off;


% Wrapper coded by: okantt
% LSD Copyright (c) 2007-2010 rafael grompone von gioi 
% Revision History:
% Rev 0 : Initial Release

    p = inputParser;
    p.FunctionName = 'LSD MATLAB Wrapper';
    p.addRequired('im', @isreal );
    p.addParamValue('scale', 0.8, @(x) isreal(x) && x >= 0);
    p.addParamValue('sigma_coef', 0.6, @(x) isreal(x) && x >= 0);
    p.addParamValue('quant', 2, @(x) isreal(x) && x >= 0);
    p.addParamValue('ang_th', 22.5, @(x) isreal(x) && x >= 0 && x <= 180);
    p.addParamValue('eps', 0, @isreal);
    p.addParamValue('density_th', 0.7, @(x) isreal(x) && x >= 0 && x <= 1);
    p.addParamValue('n_bins', 1024, @(x) isinteger(x) && x >= 1);
    p.addParamValue('max_grad', 255, @(x) isreal(x) && x >= 1);

    p.addParamValue('reg', '', @ischar);
    p.addParamValue('epsfile', '', @ischar);
    p.addParamValue('svgfile', '', @ischar);

    p.addParamValue('width', 1.5, @isreal);
    p.parse(im, varargin{:});

    im = p.Results.im;
    scale = p.Results.scale;
    sigma_coef = p.Results.sigma_coef;
    quant = p.Results.quant;
    ang_th = p.Results.ang_th;
    eps = p.Results.eps;
    density_th = p.Results.density_th;
    n_bins = p.Results.n_bins;
    max_grad = p.Results.max_grad;
    width = p.Results.width;
    reg = p.Results.reg;
    epsfile = p.Results.epsfile;
    svgfile = p.Results.svgfile;


    optional_cmd = '';
    if ~isempty(reg)
        optional_cmd = [optional_cmd, sprintf(' -R %s', reg)];
    end
    if ~isempty(epsfile)
        optional_cmd = [optional_cmd, sprintf(' -P %s', epsfile)];
    end
    if ~isempty(svgfile)
        optional_cmd = [optional_cmd, sprintf(' -S %s', svg_file)];
    end
    input_file = strcat(tempname, '_lsdinput.pgm');
    if strcmpi(class(im), 'uint8')
        imwrite(im, input_file);
    else
        imwrite(mat2gray(im), input_file);
    end
    output_file = strcat(tempname, '_lsdoutput.txt');
    command = sprintf('./lsd -s %g -c %g -q %g -a %g -e %g -d %g -b %d -m %g -W %g %s %s %s %s', ...
        scale, sigma_coef, quant, ang_th, eps, density_th, n_bins, max_grad, width, optional_cmd, ...
        input_file, output_file);
    system(command);
    output = load(output_file, '-ascii');
    delete(input_file);
    delete(output_file);

end